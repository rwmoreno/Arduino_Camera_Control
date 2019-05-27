/* =================================== */  
/* Execute new state / action          */  
/* =================================== */  

void FunctionExecuteProgramActions()

{
  switch (programStateNew) {
    case program_state_Start:
      action_Start();
      break;
    case program_state_SM_TimeLapse:
    case program_state_SM_TimeLapseB:
    case program_state_SM_Trigger:
    case program_state_SM_Manual:
      action_SM_All();
      break;
    case program_state_SO_TimeLapse:
      action_SO_TimeLapse(false);
      break;
    case program_state_SO_TimeLapseB:
      action_SO_TimeLapse(true);
      break;
    case program_state_SO_Trigger:
      action_SO_Trigger();
      break;
    case program_state_SO_Manual:
      action_SO_Manual();
      break;
    case program_state_Run_TimeLapse:
      action_Run_TimeLapse();
      break;
    case program_state_Run_TimeLapseB:
      action_Run_TimeLapseB();
      break;
    case program_state_Run_Trigger_Wait:
      action_Run_Trigger_Wait();
      break;
    case program_state_Run_Trigger_Ready:
      action_Run_Trigger_Ready();
      break;
    case program_state_Run_Manual:
      action_Run_Manual();
      break;
    default:
      break;  
  }
}

