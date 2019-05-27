void action_SO_Trigger()
{
  int     currentTime;

  currentTime = millis();

  switch (nunchukAction) {
    case nunchukActionZ:
      /* Z was pushed execute Trigger function */
      programStateLast = programStateNew;
      programStateNew = program_state_Run_Trigger_Wait;
      functionPrintTriggerWait();
      break;
      
    case nunchukActionC:
      /* C pressed so go back to selection menu */
      programStateLast = programStateNew;
      programStateNew = program_state_SM_Trigger;
      functionPrintSMTrigger();
      break;
      
    case nunchukActionLeft:
      if (optionCursorDelay) {
        optionCursorDelay = 0;
        functionPrintSOTrigger();
      }
      break;
    
    case nunchukActionRight:
      if (!optionCursorDelay) {
        optionCursorDelay = 1;
        functionPrintSOTrigger();
      }
      break;
    
    case nunchukActionUp:
      /* 'Up' pushed */
      programStateLast = programStateNew;
      if (!optionCursorDelay) {
        if (!optionTriggerLevel) {
          optionTriggerLevel = 1;
          functionPrintSOTrigger();
        }/* If optionTrigger changed to high */
      } /*If not on delay */
      else {
        optionTriggerDelay = optionTriggerDelay + 1;
        if (optionTriggerDelay > 999) {
           optionTriggerDelay = 999;
        } /* If optionTriggerDelay > 999 */
        functionPrintSOTrigger();
      } /* Else */
      break; /* Case nunchuckActionUp */
      
    case nunchukActionDown:
      /* 'Down' pushed */
      programStateLast = programStateNew;
      if (!optionCursorDelay)  {
        if (optionTriggerLevel) {
          optionTriggerLevel = 0;
          functionPrintSOTrigger();
        } /* If optionTrigger changed to low */
      }
      else {
        optionTriggerDelay = optionTriggerDelay - 1;
        if (optionTriggerDelay < 0) {
           optionTriggerDelay = 0;
        } /* If optionTriggerDelay <0 */
        functionPrintSOTrigger();
      } /* Else */
      break;
  } /* Switch */
} /* Function action_SO_Trigger */

void action_Run_Trigger_Wait()
{
  boolean triggerLevel;
  int     currentTime;
  

  triggerLevel = digitalRead(pinTrigger);
  currentTime = millis();
  if (nunchukAction == nunchukActionC) {
  /* C was pushed to go back in the menu */
    programStateLast = programStateNew;
    programStateNew = program_state_SO_Trigger;
    functionPrintSOTrigger();
  }
  else {
    /* C not pushed */
    if (!(optionTriggerLevel == triggerLevel)) {
      /* Level is opposite of trigger level, so need to see if it remains so long enough */
      if (triggerLowRecorded) {
        /* Opposite of trigger, and low has been recorded previously */
        if (currentTime - triggerLowTime >= triggerTimeMinOff) {
          /* Opposite of trigger long enough, change state to wair for trigger */
          programStateNew = program_state_Run_Trigger_Ready;
          functionPrintTriggerReady();
          triggerShotTaken = false;
          if (triggerLevel) {
            attachInterrupt(1, interruptTriggerShot, FALLING);
          }
          else {
            attachInterrupt(1, interruptTriggerShot, RISING);
          }
        } /* Trigger disabled long enough */
      }
      else {
        /* Trigger opposite of trigger, but low not recorded yet*/
        triggerLowRecorded = 1;
        triggerLowTime = currentTime;
      } /* Trigger recorded */
    } /* Trigger low */
    else {
    /* Trigger is enabled, so continue to wait until it is ready */
    triggerLowRecorded = 0;
    } /* Trigger is enabled */
  } /* C not pressed */
}

/* Trigger function                             */
/* Due to time sensitivity of the trigger,      */
/* the trigger is handled by an interupt        */

void action_Run_Trigger_Ready()
{

/* Need to add check for photo or C press */

  if (triggerShotTaken) {
    /* Interrupt caused photo to be taken so delay, end photo, then return to wait */
    delay(shotTriggerHold);
    detachInterrupt(1);  
    functionPhotoEnd();
    programStateLast = programStateNew;
    programStateNew = program_state_Run_Trigger_Wait;
    functionPrintTriggerWait();
  } /* Trigger shot taken */
  else {
    if (nunchukAction == nunchukActionC) {
      /* C was pushed to go back in the menu */
      programStateLast = programStateNew;
      programStateNew = program_state_SO_Trigger;
      functionPrintSOTrigger();
    } /* If C button pushed */
  } /* Else - C not pushed */
} /* action_Run_Trigger_Ready */


void interruptTriggerShot()
{
  if (!triggerShotTaken) {
    delay(optionTriggerDelay);
    digitalWrite(pinCameraFocus, HIGH);
    digitalWrite(pinCameraShot, HIGH);
    triggerShotTaken = true;
  } /* If trigger shot has not been taken yet */
} /* interuptTriggerShot */



void action_Run_Manual()
{
    
}

