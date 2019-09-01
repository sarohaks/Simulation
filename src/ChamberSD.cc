//sensitive detector for chamber

#include "ChamberSD.hh"
#include "ChamberHit.hh"
#include "PrimaryGenerator.hh"
#include "G4VUserPrimaryParticleInformation.hh"


#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4PrimaryParticle.hh"

ChamberSD::ChamberSD(G4String name)
			:G4VSensitiveDetector(name)
	{
		G4String HCname;
  		collectionName.insert(HCname="ChamberCollection");
	}

ChamberSD::~ChamberSD()
	{;}

void ChamberSD::Initialize(G4HCofThisEvent* HCE)
	{
		//G4cout<<"Initialize chamber SD"<<G4endl;
		//chamber collection   		
		static int HCID = -1;
  		fChamberCollection = new ChamberHitsCollection(SensitiveDetectorName,collectionName[0]); 
  	
			if(HCID<0)
  				{
					HCID = GetCollectionID(0); 
				}

 		HCE->AddHitsCollection(HCID,fChamberCollection);
			//setting initial history of a hit in each chamber
			for (G4int i=0; i<totchamber; i++)
    				{
                			//G4cout<<"checking total i "<<totchamber<<G4endl;
 					previousHitHistory[i] = -1;
 		       			previousHitTimeHistory[i] = 0;
				}
	}

G4bool ChamberSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
	{
		//G4cout<<"ChamberSD::ProcessHits for Chamber"<<G4endl;
    		// G4cout<<"+++++++++++aStep->GetTotalEnergy ="<<aStep->GetTotalEnergyDeposit()<<G4endl;
		//defining energy deposit		
		G4double edep = aStep->GetTotalEnergyDeposit();
		
			if(edep==0.0) return false;
		
		//defining pointer to get the information of volume & replica
    	G4TouchableHistory* theTouchable  = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable()); 
    	G4VPhysicalVolume* physVol = theTouchable->GetVolume();
		//G4PrimaryParticle* aParticle;
		//G4VUserPrimaryParticleInformation* info = aParticle->GetUserInformation();
		//G4String info = aParticle->GetUserInformation();
		//getting current chamber information    		
		G4int   currentChamberCopy = physVol->GetCopyNo();
    	G4double currentTime = aStep->GetPreStepPoint()->GetGlobalTime();
		//G4cout<<"+++++++ current Chamber Copy= "<<currentChamberCopy <<"  , condition value  " <<previousHitHistory[currentChamberCopy] <<G4endl;
    			
			if( (previousHitHistory[currentChamberCopy] !=-1 )&&( abs(previousHitTimeHistory[currentChamberCopy]-currentTime)<timeIntervals) ) 
    				{
        				// update track
        				(*fChamberCollection)[previousHitHistory[currentChamberCopy]]->AddEdep(edep);
        				(*fChamberCollection)[previousHitHistory[currentChamberCopy]]->AddInteraction();
             				//G4cout<<"Adding hits "<<G4endl;
    				} 
			else 
				{        
        				// new hit
        				
        				ChamberHit* newHit = new ChamberHit();
        					newHit->SetEdep(edep);
        					newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
        					newHit->SetTrackPDG(aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
        					//newHit->SetProcessName(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
        					newHit->SetInteractionNumber();
        					newHit->SetPosition(aStep->GetPostStepPoint()->GetPosition());
        					newHit->SetTime(currentTime);
						newHit->SetChamberID(theTouchable->GetReplicaNumber(1));     		//SKS Chamber level replication
						//newHit->SetChamberID(physVol->GetCopyNo());				//previous definition       
						newHit->SetChamberGapID(theTouchable->GetReplicaNumber(0));          
        					newHit->SetPolarizationIn(aStep->GetPreStepPoint()->GetPolarization());
        					newHit->SetPolarizationOut(aStep->GetPostStepPoint()->GetPolarization());
        					newHit->SetMomentumIn(aStep->GetPreStepPoint()->GetMomentum());
        					newHit->SetMomentumOut(aStep->GetPostStepPoint()->GetMomentum());
							//newHit->SetParticleInfo(info);
						//G4cout<<"Process name ="<<aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName	
						//()<<"ChamberCopy.........-"<<physVol->GetCopyNo()<<G4endl;
        					
						G4int id = fChamberCollection->insert(newHit);
        					previousHitHistory[currentChamberCopy] = id-1;
               					// G4cout<<"checking chambercopy "<<currentChamberCopy<<"  id-1 = "<<id-1<<G4endl;
        					previousHitTimeHistory[currentChamberCopy]= currentTime;
               					
               						if (aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()== "compt")
								{
                      							G4cout<<"Chamber_ID------------------------------------------"<<physVol->GetCopyNo()<<G4endl;
              							}
            

         
    				}
		return true;
	}

/*void ChamberSD::EndOfEvent(G4HCofThisEvent*)
{
}

void ChamberSD::clear()
{
} 

void ChamberSD::DrawAll()
{
} 

void ChamberSD::PrintAll()
{
} 
*/
