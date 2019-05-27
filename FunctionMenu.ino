/* =================================== */
/* Start actions (not used currently)  */
/* =================================== */

void action_Start()
{
}

/* =================================== */
/* Function for all main menu actions  */
/* =================================== */

void action_SM_All()
{
  if (nunchukAction == nunchukActionZ) {
    /* Z was pushed */
    programStateLast = programStateNew;
    programStateNew = programStateNew+1;
  }
  else {
    /* Z was not pushed */
    if (nunchukAction == nunchukActionDown) {
      /* 'Down' pushed */
      programStateLast = programStateNew;
      programStateNew = programStateNew + 10;
      if (programStateNew > 50) {
        programStateNew = 10;
      } /* if ProgramStateNew > 40 */
    } /* Down pushed */
    else {
      /* Z not pushed, and 'Down' not pushed */
      if (nunchukAction == nunchukActionUp) {
        /* 'Up' pushed */
        programStateLast = programStateNew;
        programStateNew = programStateNew - 10;
        if (programStateNew < 10) {
          programStateNew = 50;
        } /* If programStateNew < 10 */
      } /* If 'Up' pushed */
      else {
            programStateLast = programStateNew;
      } /* Else 2 */
    } /* Else */
  }/* Z not pushed */

  if (programStateLast != programStateNew) {
    lcd.clear();
    if (programStateNew % 10 == 0) {
      switch (programStateNew) {
      case program_state_SM_TimeLapse:
        functionPrintSMTimeLapse();
        break;
      case program_state_SM_TimeLapseB:
        optionCursorDelay = 1;
        functionPrintSMTimeLapseB();
        break;
      case program_state_SM_Trigger:
        optionCursorDelay = 0;
        functionPrintSMTrigger();
        break;
      case program_state_SM_Manual:
        functionPrintSMManual();
        break;
      case program_state_SM_Options:
        functionPrintSMOption();
        break;
      default:
        lcd.print("Error");
        break;
      } /* Switch statement */
    } /* New state is Set Mode menu */
    else {
      switch (programStateNew) {
      case program_state_SO_TimeLapse:
        functionPrintSOTimeLapse();
        break; 
      case program_state_SO_TimeLapseB:
        functionPrintSOTimeLapseB();
        break;
      case program_state_SO_Trigger:
        functionPrintSOTrigger();
        break;
      case program_state_SO_Manual:
        functionPrintSOManual();
        break;
      case program_state_SO_Option:
        functionPrintSOOption();
        lcd.setCursor(13,1);
        functionPrintTriggerDelay(optionBacklightOffTime);
        break;
      default:
        break;
      } /* Switch statement */
    } /* Else statement */
  } /* If program state changes */
} /* Function */

void action_SO_Manual()
{
  if (nunchukAction == nunchukActionZ) {
    /* Z pressed */
    functionPhotoShot();
  }
  else if (nunchukAction == nunchukActionC) {
    /* C pressed */
    functionPrintSMManual();
    programStateLast = programStateNew;
    programStateNew = program_state_SM_Manual;
  } /* If C pressed */    
}


/* ======================================== */
/* Function for setting Backlight off time  */
/* ======================================== */

void action_SO_Option()
{
  switch (nunchukAction) {
    case nunchukActionZ:
      /* Z Pushed so no action ---------------------------------*/
    break;
    case nunchukActionC:
      Serial.println("C Pressed");
      /* C Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      programStateNew = program_state_SM_Options;
      functionPrintSMOption();
    break;
    case nunchukActionUp:
      /* Up Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      optionBacklightOffTime = optionBacklightOffTime + 1;
      if (optionBacklightOffTime > 600) {
        optionBacklightOffTime = 600;
      } /* If bulbTime <1 */
      lcdTurnOffTime = optionBacklightOffTime * 1000;
      lcd.setCursor(13,1);
      functionPrintTriggerDelay(optionBacklightOffTime);
      break;
    case nunchukActionDown:
      /* Down Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      optionBacklightOffTime = optionBacklightOffTime - 1;
      if (optionBacklightOffTime < 10) {
        optionBacklightOffTime = 10;
      } /* If bulbTime <1 */
      lcdTurnOffTime = optionBacklightOffTime * 1000;
      lcd.setCursor(13,1);
      functionPrintTriggerDelay(optionBacklightOffTime);
    break;
  } /* Case */
} /* action_SO_Option() */

