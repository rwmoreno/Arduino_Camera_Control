/* =================================== */  
/* Check for release of previous state */  
/* =================================== */  

void FunctionCheckNunchukRelease()

{
  if (nunchukC.state == nunchuk_state_buttonPressed) {
     if (!nunchuk.cButton) {
       if (nunchukC.releaseRecorded) {
         if ((timeCurrent - nunchukC.releaseTime) > nunchuk_Min_Release) {
          nunchukC.state = nunchuk_state_buttonReleased;
         } /* End of if statement checking time held */
       } /* End of if statement checking if release has been recorded */
       else {   /* Release has not yet been recorded */
         nunchukC.releaseRecorded = 1;
         nunchukC.releaseTime = timeCurrent;
       } /* End of else in case release has not been recorded */
     } /* End of else checking to see if Up is still held */
  }
  
  if (nunchukZ.state == nunchuk_state_buttonPressed) {
     if (!nunchuk.zButton) {
       if (nunchukZ.releaseRecorded) {
         if ((timeCurrent - nunchukZ.releaseTime) > nunchuk_Min_Release) {
          nunchukZ.state = nunchuk_state_buttonReleased;
         } /* End of if statement checking time held */
       } /* End of if statement checking if release has been recorded */
       else {   /* Release has not yet been recorded */
         nunchukZ.releaseRecorded = 1;
         nunchukZ.releaseTime = timeCurrent;
       } /* End of else in case release has not been recorded */
     } /* End of else checking to see if Up is still held */
  }
    
  
  switch (nunchukY.state) {
        /* Down Case */
        case nunchuk_state_dialLow:
          if (nunchuk.analogY > nunchuk_Y_release_down) {
            /* Down press has been released */
            if (nunchukY.releaseRecorded) {
              if ((timeCurrent - nunchukY.releaseTime) > nunchuk_Min_Release) {
               nunchukY.state = nunchuk_state_dialCenter;
               nunchukY.inRepeatMode = false;
              } /* End of if statement checking time held */
            } /* End of if statement checking if release has been recorded */
            else {   /* Release has not yet been recorded */
              nunchukY.releaseRecorded = 1;
              nunchukY.releaseTime = timeCurrent;
              nunchukY.inRepeatMode = false;
            } /* End of else in case release has not been recorded */
          } /* End of else checking to see if Down is still held */
          break;

        /* Up Case*/
        case nunchuk_state_dialHigh:
          if (nunchuk.analogY < nunchuk_Y_release_up) {
            /* Up press has been released */
            if (nunchukY.releaseRecorded) {
              if ((timeCurrent - nunchukY.releaseTime) > nunchuk_Min_Release) {
                nunchukY.state = nunchuk_state_dialCenter;
                nunchukY.inRepeatMode = false;
              } /* End of if statement checking time held */
            } /* End of if statement checking if release has been recorded */
            else {   /* Release has not yet been recorded */
              nunchukY.releaseRecorded = 1;
              nunchukY.releaseTime = timeCurrent;
              nunchukY.inRepeatMode = false;
            } /* End of else in case release has not been recorded */
          } /* End of else checking to see if Up is still held */
          break;
  }

  switch (nunchukX.state) {

        /* Left Case */
        case nunchuk_state_dialLow:
          if (nunchuk.analogX > nunchuk_X_release_left) {
            if (nunchukX.releaseRecorded) {
              if ((timeCurrent - nunchukX.releaseTime) > nunchuk_Min_Release) {
               nunchukX.state = nunchuk_state_dialCenter;
              } /* End of if statement checking time held */
            } /* End of if statement checking if release has been recorded */
            else {   /* Release has not yet been recorded */
              nunchukX.releaseRecorded = 1;
              nunchukX.releaseTime = timeCurrent;
            } /* End of else in case release has not been recorded */
          } /* End of else checking to see if Up is still held */
          break;
 
        /* Right Case*/
        case nunchuk_state_dialHigh:
          if (nunchuk.analogX < nunchuk_X_release_right) {
            if (nunchukX.releaseRecorded) {
              if ((timeCurrent - nunchukX.releaseTime) > nunchuk_Min_Release) {
               nunchukX.state = nunchuk_state_dialCenter;
              } /* End of if statement checking time held */
            } /* End of if statement checking if release has been recorded */
            else {   /* Release has not yet been recorded */
              nunchukX.releaseRecorded = 1;
              nunchukX.releaseTime = timeCurrent;
            } /* End of else in case release has not been recorded */
          } /* End of else checking to see if Up is still held */
          break;

      }
}

/* =================================== */  
/* Check for new state / action        */  
/* =================================== */  

void FunctionCheckNunchukAction()

{
  /* Check for action based on C button press */
  if (nunchuk.cButton) {
    if (nunchukC.state != nunchuk_state_buttonPressed) {
      nunchukC.state = nunchuk_state_buttonPressed;
      nunchukC.releaseRecorded = 0;
      nunchukC.action = nunchuk_action_buttonPress;
     }
     else {
       nunchukC.action = nunchuk_action_None;
     }
   }
   else {
     nunchukC.action = nunchuk_action_None;
   }     
   
  /* Check for action based on Z button press */
   if (nunchuk.zButton) {
     if (nunchukZ.state != nunchuk_state_buttonPressed) {
       nunchukZ.state = nunchuk_state_buttonPressed;
       nunchukZ.releaseRecorded = 0;
       nunchukZ.action = nunchuk_action_buttonPress;
     }
     else {
       nunchukZ.action = nunchuk_action_None;
     }
   }
   else {
     nunchukZ.action = nunchuk_action_None;
   }

  /* Check for actions based on Up / Down joystick motion */   
  if (nunchuk.analogY < nunchuk_Y_trigger_down) {
    /* Nunchuk joystick is down */
    if (nunchukY.state != nunchuk_state_dialLow) {
      nunchukY.state = nunchuk_state_dialLow;
      nunchukY.releaseRecorded = 0;
      nunchukY.action = nunchuk_action_dialLow;
      nunchukY.lastActionTime = timeCurrent;
      nunchukY.inRepeatMode = false;
    }
    else {
      if (nunchukY.inRepeatMode) {
        /* In repeat mode */
        if ( (timeCurrent - nunchukY.lastActionTime) >= nunchukRepeatOngoing ) {
          nunchukY.action = nunchuk_action_dialLow;
          nunchukY.lastActionTime = timeCurrent;
        } /* If time to repeat action, while in repeat mode */
        else {
          nunchukY.action = nunchuk_action_None;
        } /* Else */
      } /* If in repeat mode */
      else {
        /* Not in repeat mode yet */
        if ( (timeCurrent - nunchukY.lastActionTime) >= nunchukRepeatStart ) {
          nunchukY.inRepeatMode = true;
          nunchukY.action = nunchuk_action_dialLow;
          nunchukY.lastActionTime = timeCurrent;
        } /* If time to begin repeat action */
        else {
          nunchukY.action = nunchuk_action_None;
        } /* Else */
      } /* Else */
    } /* Else */
  }
  else {
    /* Nunchuk joystick is not down */
    if (nunchuk.analogY > nunchuk_Y_trigger_up) {
      /* Nunchuk joystick is up */
      if (nunchukY.state != nunchuk_state_dialHigh) {
        /* Nunchuk joystick is up but not yet in up state */
        nunchukY.state = nunchuk_state_dialHigh;
        nunchukY.releaseRecorded = 0;
        nunchukY.action = nunchuk_action_dialHigh;
        nunchukY.lastActionTime = timeCurrent;
        nunchukY.inRepeatMode = false;
      }
      else {
        /* Nunchuk joystick is up and in up state */
        if (nunchukY.inRepeatMode) {
          /* Nunchuk joystick is up, in up state, and in repeat mode */
          if ( (timeCurrent - nunchukY.lastActionTime) >= nunchukRepeatOngoing ) {
          /* Nunchuk joystick is up, in up state, in repeat mode and ready for a repeat*/            
            nunchukY.action = nunchuk_action_dialHigh;
            nunchukY.lastActionTime = timeCurrent;
          } /* If time to repeat action, while in repeat mode */
          else {
          /* Nunchuk joystick is up, in up state, in repeat mode and NOT ready for a repeat*/            
            nunchukY.action = nunchuk_action_None;
          } /* Else */
        } /* If in repeat mode */
        else {
          /* Nunchuk joystick is up, in up state, and NOT in repeat mode */
          if ( (timeCurrent - nunchukY.lastActionTime) >= nunchukRepeatStart ) {
            /* Nunchuk joystick is up, in up state, NOT in repeat mode, but ready to start repeat mode */
            nunchukY.inRepeatMode = true;
            nunchukY.action = nunchuk_action_dialHigh;
            nunchukY.lastActionTime = timeCurrent;
          } /* If time to begin repeat action */
          else {
            /* Nunchuk joystick is up, in up state, NOT in repeat mode, and NOT ready to start repeat mode */
            nunchukY.action = nunchuk_action_None;
          } /* Else */
        } /* Else */
      } /* Else */
    }
    else {
      /* Nunchuk joystick is NOT up or down */
      nunchukY.action = nunchuk_action_None;
      nunchukY.state = nunchuk_state_dialCenter;
    } /* Else */
  } /* Else */
  
  /* Check for actions based on Left / Right joystick motion */   
  if (nunchuk.analogX < nunchuk_X_trigger_left) {
    if (nunchukX.state != nunchuk_state_dialLow) {
      nunchukX.state = nunchuk_state_dialLow;
      nunchukX.releaseRecorded = 0;
      nunchukX.action = nunchuk_action_dialLow;
    }
    else {
      nunchukX.action = nunchuk_action_None;
    }
  }
  else if (nunchuk.analogX > nunchuk_X_trigger_right) {
    if (nunchukX.state != nunchuk_state_dialHigh) {
      nunchukX.state = nunchuk_state_dialHigh;
      nunchukX.releaseRecorded = 0;
      nunchukX.action = nunchuk_action_dialHigh;
    }
    else {
      nunchukX.action = nunchuk_action_None;
    }
  }
  else {
    nunchukX.action = nunchuk_action_None;
  }
  
  /* Screen so that only one function is returned */
  if (nunchukZ.action == nunchuk_action_buttonPress) {
    nunchukAction = nunchukActionZ;
    lcdLastActionTime = timeCurrent;
  }
  else if (nunchukC.action == nunchuk_action_buttonPress) {
    nunchukAction = nunchukActionC;
    lcdLastActionTime = timeCurrent;
  }
  else if (nunchukY.action == nunchuk_action_dialLow) {
    nunchukAction = nunchukActionDown;
    lcdLastActionTime = timeCurrent;
  }
  else if (nunchukY.action == nunchuk_action_dialHigh) {
    nunchukAction = nunchukActionUp;
    lcdLastActionTime = timeCurrent;
  }
  else if (nunchukX.action == nunchuk_action_dialLow) {
    nunchukAction = nunchukActionLeft;
    lcdLastActionTime = timeCurrent;
  }
  else if (nunchukX.action == nunchuk_action_dialHigh) {
    nunchukAction = nunchukActionRight;
    lcdLastActionTime = timeCurrent;
  }
  else {
    nunchukAction = nunchukActionNone;
  }
//  Serial.print("Action = ");
//  Serial.println(nunchukAction);
}

