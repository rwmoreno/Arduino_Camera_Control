void action_SO_TimeLapse(boolean bulbMode)
{
  switch (nunchukAction) {
    case nunchukActionZ:
      /* Z Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      functionPrintTimeLapseRun();
      triggerTime = millis();
      triggerTimeAdj = triggerTime;
      if (!bulbMode) {
        /* Take a picture, change display, and change mode */
        functionPhotoShot();
        countdownTime = optionDelayTime;
        functionPrintTimeLapseTime();
        countdownTimeDisplayed = countdownTime;
        programStateNew = program_state_Run_TimeLapse;
      }
      else {
        functionPhotoBegin();
        countdownTime = optionDelayTimeB;
        functionPrintTimeLapseTime();
        countdownTimeDisplayed = countdownTime;
        programStateNew = program_state_Run_TimeLapseB;
      }
    break;
    case nunchukActionC:
      /* C Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      if (!bulbMode) {
        programStateNew = program_state_SM_TimeLapse;
        functionPrintSMTimeLapse();
      }
      else {
        programStateNew = program_state_SM_TimeLapseB;
        functionPrintSMTimeLapseB();
      }
    break;
    case nunchukActionUp:
      /* Up Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      if (bulbMode && !optionCursorDelay) {
        /* Up Pushed, in bulb mode, cursor on bulb time-------------------*/
        optionBulbTime = optionBulbTime + 1;
        if (optionBulbTime > optionDelayTimeB - 1) {
          optionBulbTime = optionDelayTimeB - 1;
        } /* If bulbTime > optionDelayTimeB - 1 */
      } /* bulbMode && !optionBulbTime */
      else {
        if (bulbMode) {
        /* Up Pushed, in bulb mode, cursor on delay time-------------------*/
          optionDelayTimeB = optionDelayTimeB + 1;
          if (optionDelayTimeB > 1800) {
            optionDelayTimeB = 1800;
          } /* If optionDelayTime > 1800 */
        }
        else {
        /* Up Pushed, not in bulb mode, cursor on delay time---------------*/
          optionDelayTime = optionDelayTime + 1;
          if (optionDelayTime > 1800) {
            optionDelayTime = 1800;
          } /* If optionDelayTime > 1800 */
        } /* Not bulb mode */
      } /* Else */
      if (!bulbMode) {
        functionPrintSOTimeLapse();
      }
      else {
        functionPrintSOTimeLapseB();
      } /* Else */
    break;
    case nunchukActionDown:
      /* Down Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      if (bulbMode && !optionCursorDelay) {
        /* Down Pushed, in bulb mode, cursor on bulb time-------------------*/
        optionBulbTime = optionBulbTime - 1;
        if (optionBulbTime < 1) {
          optionBulbTime = 1;
        } /* If bulbTime <1 */
      } /* bulbMode && !optionBulbTime */
      else {
        /* Down Pushed, in bulb mode, cursor on delay time------------------*/
        if (bulbMode) {
          optionDelayTimeB = optionDelayTimeB - 1;
          if (optionDelayTimeB < (optionBulbTime + 1)) {
            optionDelayTimeB = optionBulbTime + 1;
          } /* If optionDelayTime < 5 */
        }
        else {
        /* Down Pushed, not in bulb mode, cursor on delay time---------------*/
          optionDelayTime = optionDelayTime - 1;
          if (optionDelayTime < 5) {
            optionDelayTime = 5;
          } /* If optionDelayTime < 5 */
        } /* Not bulb mode */
      } /* Else */
      if (!bulbMode) {
        functionPrintSOTimeLapse();
      }
      else {
        functionPrintSOTimeLapseB();
      } /* Else */
    break;
  } /* Case */
  if (bulbMode) {
    /* Only check Rigth and Left buttons if in Bulb Mode */
    switch (nunchukAction) {
      case nunchukActionLeft:
        /* Left pushed, so change cursor to Delay time */
        if (!optionCursorDelay) {
          optionCursorDelay = 1;
          functionPrintSOTimeLapseB();
        } /* If cursor previously on bulb time */
      break;
      case nunchukActionRight:
        if (optionCursorDelay) {
          optionCursorDelay = 0;
          functionPrintSOTimeLapseB();
        } /* If cursor previously on time for time lapse */
    default:
    break;
    } /* Switch */
  } /* If bulbMode */
} /* action_SO_Timelapse */


/* Run Time Lapse until Z is pushed */
void action_Run_TimeLapse()
{
  unsigned long currentTime;

  switch (nunchukAction) {
    case nunchukActionC:
      /* C was pushed */
      programStateLast = programStateNew;
      programStateNew = program_state_SO_TimeLapse;
      functionPrintSOTimeLapse();
      break;
    default:
      currentTime = millis();
      countdownTime =  (int) ((((unsigned long) optionDelayTime * 1000) - (currentTime - triggerTimeAdj))/1000)+1;
      if (countdownTime != countdownTimeDisplayed) {
        functionPrintTimeLapseTime();
        countdownTimeDisplayed = countdownTime;
      } /* If countdown time is not same as displayed */
      if ( (currentTime - triggerTimeAdj) >= ((long) optionDelayTime * 1000) ) {
        functionPhotoShot();  /* Take a picture */
        triggerTimeAdj = triggerTimeAdj + (long) optionDelayTime * 1000;
      }/* If time for photo */
  } /* switch */
} /* Action_Run_TimeLapse */

/* Run Time Lapse until C is pushed */
void action_Run_TimeLapseB()
{
  unsigned long currentTime;

  switch (nunchukAction) {
    case nunchukActionC:
      /* C was pushed */
      if (inBulbShot) {
          functionPhotoEnd();
      }
      programStateLast = programStateNew;
      programStateNew = program_state_SO_TimeLapseB;
      functionPrintSOTimeLapseB();
      break;
    default:
      currentTime = millis();
      if (inBulbShot) {
        /* In bulb shot, see if dispay must change */
        countdownTime =  (int) ((((unsigned long) optionBulbTime * 1000) - (currentTime - triggerTime))/1000)+1;
        if (countdownTime != countdownTimeDisplayed) {
          functionPrintTimeLapseTime();
          countdownTimeDisplayed = countdownTime;
        } /* If countdown time is not same as displayed */
        if ( (currentTime - triggerTime) >= ((long) optionBulbTime * 1000) ) {
          functionPhotoEnd();
        } /* If bulb time is met */ 
      } /* In bulb shot */
      else {
        /* Not in bulb shot */
        /* See if dispay must change */
        countdownTime =  (int) ((((unsigned long) optionDelayTimeB * 1000) - (currentTime - triggerTimeAdj))/1000)+1;
        if (countdownTime != countdownTimeDisplayed) {
          functionPrintTimeLapseTime();
          countdownTimeDisplayed = countdownTime;
        } /* If countdown time is not same as displayed */
        if ( (currentTime - triggerTimeAdj) >= ((long) optionDelayTimeB * 1000) ) {
          functionPhotoBegin();
          triggerTime = currentTime;
          triggerTimeAdj = triggerTimeAdj + ((long) optionDelayTimeB * 1000);
        }/* If ready for next shot */
      }/* Else */
  }/* Switch */
} /* action_Run_TimeLapseB */



