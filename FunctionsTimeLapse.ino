void action_SO_TimeLapse(boolean bulbMode)
{
  switch (nunchukAction) {
    case nunchukActionZ:
      /* Z Pushed ------------------------------------------------------*/
      programStateLast = programStateNew;
      functionPrintTimeLapseRun();
      triggerTime = millis();
      if (!bulbMode) {
        functionPhotoShot();  /* Take a picture */
        programStateNew = program_state_Run_TimeLapse;
      }
      else {
        functionPhotoBegin();
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


/* Run Time Lapse until Z is pusshed */
void action_Run_TimeLapse()
{
  int currentTime;

  switch (nunchukAction) {
    case nunchukActionC:
      /* C was pushed */
      programStateLast = programStateNew;
      programStateNew = program_state_SO_TimeLapse;
      functionPrintSOTimeLapse();
      break;
    default:
      currentTime = millis();
      if ( (currentTime - triggerTime) >= optionDelayTime * 1000) {
        functionPhotoShot();  /* Take a picture */
        triggerTime = currentTime;
      }/* If time for photo */
  } /* switch */
} /* Action_Run_TimeLapse */

/* Run Time Lapse until C is pushed */
void action_Run_TimeLapseB()
{
  int currentTime;

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
        if ( (currentTime - triggerTime) >= optionBulbTime * 1000) {
          functionPhotoEnd();
        } /* If bulb time is met */
      } /* In bulb shot */
      else {
        if ( (currentTime - triggerTime) >= optionDelayTimeB * 1000) {
          functionPhotoBegin();
          triggerTime = currentTime;
        }/* If ready for next shot */
      }/* Else */
  }/* Switch */
} /* action_Run_TimeLapseB */



