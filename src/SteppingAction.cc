//action to be done for each step

//user defined header file include
#include "SteppingAction.hh"

//geant4 includes
#include "G4TransportationManager.hh" 

SteppingAction::SteppingAction()
	{
     		G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->SetPushVerbosity(0);
	}

SteppingAction::~SteppingAction()
	{}
