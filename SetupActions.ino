/* ======================= */  
/* ======================= */  
/* Setup Actions           */  
/* ======================= */  
/* ======================= */  

void setup() {                
    /* Initialize the Serial Port */
    Serial.begin(BAUDRATE);
    Serial.flush();
//    Serial.println("Starting.....");
    
    /* Initiate each output pin */ 
    pinMode(pinCameraFocus, OUTPUT);
    pinMode(pinCameraShot, OUTPUT);
    pinMode(pinLcdPower, OUTPUT);
    pinMode(pinLCD_RS, OUTPUT);
    pinMode(pinLCD_RW, OUTPUT);
    pinMode(pinLCD_RW, OUTPUT);
    pinMode(pinLCD_Enable, OUTPUT);
    pinMode(pinLCD_DB4, OUTPUT);
    pinMode(pinLCD_DB5, OUTPUT);
    pinMode(pinLCD_DB6, OUTPUT);
    pinMode(pinLCD_DB7, OUTPUT);
    pinMode(pinTrigger, INPUT);
    
    /* Initialize the LCD */
    lcd.begin(16, 2);                    /* set up the LCD's number of columns and rows */
    lcd.clear();                         /* Clear the LCD */
    digitalWrite(pinLcdPower, LOW);     /* Make sure the LCD backlight is enabled */
    lcdBacklightOff = false;
    lcdLastActionTime = millis();
    
    /* Initialize the Wii Nunchuk */
    nunchuk.init();
    
    /* Set initial pin values */ 
    digitalWrite(pinCameraFocus, LOW);
    digitalWrite(pinCameraShot, LOW);

    /* Set initial and "last" program state */
    programStateLast = program_state_SM_TimeLapse;
    programStateNew = program_state_SM_TimeLapse;

    /* Write to the screen */    
    functionPrintSMTimeLapse();

    /* Set initial nunchuk state */
    nunchukX.state = nunchuk_state_dialCenter;
    nunchukY.state = nunchuk_state_dialCenter;
    nunchukC.state = nunchuk_state_buttonReleased;
    nunchukZ.state = nunchuk_state_buttonReleased;

    nunchukX.inRepeatMode = false;
    nunchukY.inRepeatMode = false;

    /* Set initial nunchuk actions */
    nunchukX.action = nunchuk_action_None;
    nunchukY.action = nunchuk_action_None;
    nunchukC.action = nunchuk_action_None;
    nunchukZ.action = nunchuk_action_None;

    /* Set default options */
    optionDelayTime      =  30; /* Default delay time in seconds*/
    optionDelayTimeB     = 300;  /* Default delay time for bulb option, in seconds */
    optionBulbTime       =  30; /* Default bulb time in seconds */
    optionTriggerDelay   =   0; /* Default delay between trigger enabled and photo shot */
    optionCursorDelay    =   1; /* Default to cursor on delay for Bulb options screen*/
    optionTriggerLevel   =   0; /* Trigger on low */
    
    /* Not in middle of bulb shot */
    inBulbShot = 0;

    /* Trigger low not yeat recoreded */    
    triggerLowRecorded = 0;
  }

