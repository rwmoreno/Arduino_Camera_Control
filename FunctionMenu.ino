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
      if (programStateNew > 40) {
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
          programStateNew = 40;
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

