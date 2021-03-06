/*

 Application to allow MCU control of camera
 
 Supports the following functions:
 - Interval shots
 - Interval shots with Bulb function (variable exposure time)
 - Trigger shots (e.g., with laser trigger)
 - Manual shots
 
 Other features:
 - Control is via Wii Nunchuk adaptor
 - Uses LCD display for status, menus, etc.
 - Designed for Canon 40D camera with two controls: Focus, Shutter
 
*/

/* Include the required libraries */

#include <Wire.h>
#include <LiquidCrystal.h>
#include "ArduinoNunchuk.h"

/* Definition of connections to Arduino */

#define pinCameraFocus        7
#define pinCameraShot         8
#define pinLcdPower          13

#define pinLCD_RS             4
#define pinLCD_RW             5
#define pinLCD_Enable         6
#define pinLCD_DB4            9
#define pinLCD_DB5           10
#define pinLCD_DB6           11
#define pinLCD_DB7           12

#define pinTrigger            3 /* Do not change as it is tied to interupt 1 for the trigger */

/* Definitions of default positions on Wii Nunchuck */
#define nunchuk_X_trigger_left   60
#define nunchuk_X_release_left   90
#define nunchuk_X_trigger_right 190
#define nunchuk_X_release_right 160
#define nunchuk_Y_trigger_down   60
#define nunchuk_Y_release_down   90
#define nunchuk_Y_trigger_up    190
#define nunchuk_Y_release_up    160

/* Definitions for nunchuk debounce */
#define nunchuk_Min_Release  100

/* Define minimum time for trigger to be off before waiting for next trigger */
#define triggerTimeMinOff    100

/* Definitions of Nunchuck actions */
#define nunchuk_action_None         0
#define nunchuk_action_dialLow      1
#define nunchuk_action_dialHigh     2
#define nunchuk_action_buttonPress  3

/* Definitions of Nunchuck states */
#define nunchuk_state_buttonReleased   0
#define nunchuk_state_buttonPressed    1

#define nunchuk_state_dialLow          0
#define nunchuk_state_dialCenter       1
#define nunchuk_state_dialHigh         2

/* Definitions of Program states */
#define program_state_Start              0
#define program_state_SM_TimeLapse      10
#define program_state_SM_TimeLapseB     20
#define program_state_SM_Trigger        30
#define program_state_SM_Manual         40
#define program_state_SO_TimeLapse      11
#define program_state_SO_TimeLapseB     21
#define program_state_SO_Trigger        31
#define program_state_SO_Manual         41
#define program_state_Run_TimeLapse     12
#define program_state_Run_TimeLapseB    22
#define program_state_Run_Trigger_Wait  32
#define program_state_Run_Trigger_Ready 33
#define program_state_Run_Manual        42

#define nunchukActionNone                0
#define nunchukActionZ                   1
#define nunchukActionC                   2
#define nunchukActionUp                  3
#define nunchukActionDown                4
#define nunchukActionLeft                5
#define nunchukActionRight               6

#define nunchukRepeatStart             1000   /* Time in milliseconds until repeat action begins (in milliseconds) */  
#define nunchukRepeatOngoing             50   /* Fequency of repeating action once repeating is triggered (in milliseconds) */

/* Define camera photo parameters */
#define shotFocusHold       0    /* Defines how long to hold focus pin high before taking a picture */
#define shotTriggerHold   500    /* Defines how long to hold trigger pin high during photo (non aplicable to Bulb pictures) */
#define shotFocusHoldPost   0    /* Defines how long to hold the focus pin high after taking a picture */

/* Defines how long to wait until backlight turns off */
#define lcdTurnOffTime   30000

/* Other miscellaneous definitions */
#define BAUDRATE 19200

/* Set up LCD and Nunchuck objects */

LiquidCrystal lcd(pinLCD_RS,pinLCD_RW,pinLCD_Enable,pinLCD_DB4,pinLCD_DB5,pinLCD_DB6,pinLCD_DB7);
ArduinoNunchuk nunchuk = ArduinoNunchuk();

/* Program control variables */

int programStateNew;
int programStateLast;
int nunchukAction;

/* Structures and variables for nunchuk */

struct button {
  int state;
  int action;
  int releaseTime;
  boolean releaseRecorded;
};

button nunchukC, nunchukZ;

struct dial {
  int state;
  int action;
  int lastActionTime;
  boolean inRepeatMode;
  int releaseTime;
  boolean releaseRecorded;
};

dial nunchukX, nunchukY;


/* Photo control variables (modified by users) */

int timeCurrent;                 /* Latest time measured */
int timeLastPhoto;               /* Time of last photo (when photo began) */
boolean inBulbShot;              /* Tells if in middle of bulb shot */

/* User selectable options for interval and interval - bulb photos */
int optionDelayTime;             /* Time selected by user for delay between shots (in seconds) */
int optionDelayTimeB;            /* Delay time for Bulb option */
int optionBulbTime;              /* Time selected by user for Bulb exposure (in seconds) */
int optionTriggerDelay;          /* Time to delay before shooting a trigger shot */
boolean optionCursorDelay;        /* Defines if curson is on Delay (1) or Shutter time (0) */
                                  /* For Trigger, defined if cursor is on Delay (1) or Trigger level (0) */

int triggerTime;                 /* Last time a photo was taken or trigger was activated */
int triggerLowTime;              /* First time low trigger was recorded */
boolean triggerLowRecorded;      /* Indicates if a low trigger has already been recorded */
volatile boolean triggerShotTaken;         /* Indicated if a trigger shot was taken through an interupt */

boolean optionTriggerLevel;      /* Define if trigger activated by low or high on pin */
                                 /*   0 = trigger on Low  1= trigger on High          */
                                 
/* LCD related variables */
boolean lcdBacklightOff;                /* Tells if LCD is on or off */
int     lcdLastActionTime;             /* Last time there was an action wiht nunchuk */
 
/* Counter variable */

int counter;

/* ======================= */
/* ======================= */
/* Main Program            */
/* ======================= */
/* ======================= */

void loop() {

  nunchuk.update();                 /* Get current nunchuk status */
  timeCurrent = millis();           /* Record time of last read   */
  FunctionCheckNunchukRelease();    /* Check for release of previous nunchuk actions  */
  FunctionCheckNunchukAction();     /* Check for new nunchuk actions */
  /* Check if LCD is active, if so, just execute the action, if not intercept and nunchuk action */
  if (lcdBacklightOff) {
    /* LCD is off, so see if a nunchuk action has been given */
    if (nunchukAction != nunchukActionNone) {
      /* Nunchuk was used to bring LCD back on and set state */
      digitalWrite(pinLcdPower, LOW);     /* Enable LCD backlight */
      lcdBacklightOff = false;
      nunchukAction = nunchukActionNone;
    } /* If LCD was off and nunchuk action detected */
  } /* If LCD was off and no nunchuk action detected */
  else {
    /* LCD Backlight is on, so see if it should be turned off */
    if ( (nunchukAction == nunchukActionNone) && ((timeCurrent - lcdLastActionTime) >= lcdTurnOffTime) ) {
      digitalWrite(pinLcdPower, HIGH);     /* Disable LCD backlight */
      lcdBacklightOff = true;
    } /* If no action and time to turn LCD off */
  } /* Else - backlight on) */
  FunctionExecuteProgramActions();  /* If active, un current action based on current program state */
}


