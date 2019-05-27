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
      programStateNew = program_state_SM_Trigger;
      functionPrintSMTrigger();
      break;
    case nunchukActionUp:
      /* 'Up' pushed */
      programStateLast = programStateNew;
      if (!optionTriggerLevel) {
        optionTriggerLevel = 1;
        functionPrintSOTrigger();
      }/* If optionTrigger changed to high */
      break;
    case nunchukActionDown:
      /* 'Down' pushed */
      programStateLast = programStateNew;
      if (optionTriggerLevel) {
        optionTriggerLevel = 0;
        functionPrintSOTrigger();
      } /* If optionTrigger changed to low */
      break;
  }
} /* Function action_SO_Trigger */

void action_Run_Trigger_Wait()
{
  boolean triggerLevel;
  int     currentTime;
  
  Serial.println("In action_Run_Trigger_Wait");
  triggerLevel = digitalRead(pinTrigger);
  Serial.print("optionTriggerLevel = ");
  Serial.println(optionTriggerLevel);
  Serial.println("triggerLevel = ");
  Serial.println(triggerLevel);
  Serial.print("(optionTriggerLevel ^ triggerLevel) = ");
  Serial.println((optionTriggerLevel ^ triggerLevel));
  Serial.println("----------------------------------");
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
        } /* Trigger disabled long enough */
      }
      else {
        /* Trigger opposit of trigger, but low not recorded yet*/
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

void action_Run_Trigger_Ready()
{
  boolean triggerLevel;
  
  triggerLevel = digitalRead(pinTrigger);
  if (nunchukAction == nunchukActionC) {
  /* C was pushed to go back in the menu */
    programStateLast = programStateNew;
    programStateNew = program_state_SO_Trigger;
    functionPrintSOTrigger();
  }
  else {
    if ( optionTriggerLevel == triggerLevel) {
      /* Photo was triggered */
      functionPhotoShot();
      programStateLast = programStateNew;
      programStateNew = program_state_Run_Trigger_Wait;
      triggerLowRecorded = 0;
      functionPrintTriggerWait();
    } /* If trigger was activated */
  } /* If C pushed */
}

void action_Run_Manual()
{
    
}

