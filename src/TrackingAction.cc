//action to be done for each track

//user defined header file includes
#include "TrackingAction.hh"
#include "Trajectory.hh"

//geant4 includes
#include "G4Track.hh"
#include "G4TrackingManager.hh"

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
	{
		// Create trajectory only for primaries 
    		fpTrackingManager->SetStoreTrajectory(true); 
    		fpTrackingManager->SetTrajectory(new Trajectory(aTrack));
		
		//if(aTrack->GetParentID()==0)
		//{ fpTrackingManager->SetStoreTrajectory(true); }
		//else
		//{ fpTrackingManager->SetStoreTrajectory(false); }
 	}

void TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
	{}
