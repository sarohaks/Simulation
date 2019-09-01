//Stcking action will kill the outside events

//user defined headers include
#include "StackingAction.hh"
#include "DetectorConstruction.hh"

//geant4 includes
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Navigator.hh"
#include "G4TransportationManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

StackingAction::StackingAction() 
	{
	//	theMessenger = new StackingAction(this);
		// messenger defaults
  		//killGammasFlag  = 0;

  		// global geometry navigator
  		gNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
	}

StackingAction::~StackingAction() 
	{}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack (const G4Track* aTrack, G4Step* aStep) 
	{
		static G4int gammasKilled = 0;
		
  		G4ClassificationOfNewTrack classification;

  		// Kill gammas from neutrons in concrete wall
		//if (aTrack->GetParentID() == 0)
  		//if(killGammasFlag) 
			//{
    				// check if particle is gamma
    				//G4ParticleDefinition* particleType = aTrack->GetDefinition();
   				if(aTrack->GetParentID() == 0) 
					{
						G4double zMomentum = (aTrack->GetMomentumDirection().z());
						if (zMomentum > 0.0500)       						
						// check if particle is in world_phys
      						//G4ThreeVector pos = aTrack->GetPosition();
						//if()
						//if (-5<(aStep->GetPostStepPoint()->GetPosition().z())<5)  return fUrgent; 
      						//G4ThreeVector *ptr = NULL;
      						//G4VPhysicalVolume *theVolume;
      						//theVolume = gNavigator->LocateGlobalPointAndSetup(pos,ptr,false);
      						//if(aTrack->GetNextVolume()->GetName() != "worldPhys")  return fUrgent;
						//if(theVolume->GetName() != "worldPhys")  return fUrgent;
							{
								classification = fKill;
								G4cout<<"Total Gammas killed that are outside (detectorRingPhys):"<< ++gammasKilled << G4endl;
      							}
    					}
  			//}

  	return classification;
	}

//void StackingAction::NewStage() {;}

    
//void StackingAction::PrepareNewEvent() {;}




