//sensitive detector for scintillator

#include "CalorimeterSD.hh"
#include "CalorimeterHit.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"

CalorimeterSD::CalorimeterSD(G4String name)
    		:G4VSensitiveDetector(name), totcal(16), totcell(100) //CaloHCID(-1)
	{
  		G4String HCname;
  		collectionName.insert(HCname="CalorimeterCollection");

		for (G4int i=0; i<totcal; i++)
		for(G4int j=0;j<totcell;j++)
			{
  				fCellID[i][j] = -1 ;
			}
	}

CalorimeterSD::~CalorimeterSD()
	{ 
   		// G4cout<<"++++++++++++++++++++++++++++++++++++++++Destructor:: calorimeter SD"<<G4endl;
  		//delete [] CellID;
	}

void CalorimeterSD::Initialize(G4HCofThisEvent* HCE)
	{
		//G4cout<<"Initialize calorimeter SD"<<G4endl;
        	static int HCID = -1;
  		fCalorimeterCollection = new CalorimeterHitsCollection(SensitiveDetectorName,collectionName[0]); 
	
		/*for(G4int j=0;j<fNumberOfCellsInZ;j++)
  		for(G4int k=0;k<fNumberOfCellsInPhi;k++)
  		{
    			fCellID[j][k] = -1;
  		}*/

		if(HCID<0)
  			{
				HCID = GetCollectionID(0); 
			}

 			HCE->AddHitsCollection(HCID,fCalorimeterCollection);
		
		//defiining cells in each unit of scintillator
		for (G4int i=0; i<totcal; i++)
		for (G4int j=0;j<totcell;j++)
    			{
                		//G4cout<<"checking total i "<<totcal<<G4endl;
 				fCellID[i][j] = -1;       	
				//previousHitHistory[i][j] = -1;
        			//previousHitTimeHistory[i][j] = 0;
       				//G4cout<<" no of Cell "<<totcell<<G4endl;
				/*for(G4int j=0;j<totcell;j++)
  	  		{    
				G4cout<<" j = "<<j<<G4endl;
				lastHitHistory[j] = -1;
        			lastHitTimeHistory[j] = 0; 
    				//CellID[j] = -1;
  	  		}*/
			}
	}	

G4bool CalorimeterSD::ProcessHits( G4Step* aStep, G4TouchableHistory*)
	{
		//G4cout<<"CalorimeterSD::ProcessHits for Calorimeter"<<G4endl;	
  		//defining energy deposition
		G4double edep = aStep->GetTotalEnergyDeposit();
	
		//defining true interaction		
  		if(edep<=0.0) return false;
		
		//defining pointer to touchable
		
		G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
		
		//G4VPhysicalVolume* physVol = ROhist->GetVolume();
		//G4TouchableHistory* theTouchable = (G4TouchableHistory*)( theTrack->GetTouchable() );
		//if ( theTouchable ) 
		
		G4int  currentCellCopy = theTouchable->GetReplicaNumber(0);
		
		//G4int   currentCellCopy = theTouchable->GetReplicaNumber(1);
    		//currentCopyNo = theTouchable->GetReplicaNumber( 0 );
    		
		if (theTouchable->GetHistoryDepth()>1) 
			{
				G4int currentCalorimeterCopy = theTouchable->GetReplicaNumber(1);
      				//motherCopyNo = theTouchable->GetReplicaNumber( 1 );
    			}
  		
		/*const G4VPhysicalVolume* physVol = theTouchable->GetVolume();
		G4int   currentCalorimeterCopy = physVol->GetCopyNo();
		G4int   currentCellCopy = physVol->GetCopyNo();    //new added
        	G4cout<<" Copy no = "<<currentCalorimeterCopy<<G4endl;
		G4cout<<" Copy no = "<<currentCellCopy<<G4endl;*/
  		//G4int copyID = hist->GetReplicaNumber();
		
		G4double currentTime = aStep->GetPreStepPoint()->GetGlobalTime();
		
  		//if( (previousHitHistory[currentCalorimeterCopy][currentCellCopy]!=-1)) //&& (lastHitHistory[currentCellCopy]!=-1))
	   	//&&(abs(previousHitTimeHistory[currentCalorimeterCopy][currentCellCopy]-currentTime)<timeIntervals) )
		if(fCellID[currentCalorimeterCopy][currentCellCopy]!=-1) 	
			{
        	// update track
        	//(*fCalorimeterCollection)[previousHitHistory[/*currentCalorimeterCopy*/currentCellCopy]]->AddEdep(edep);
        	//(*fCalorimeterCollection)[previousHitHistory[/*currentCalorimeterCopy*/currentCellCopy]]->AddInteraction();
		        	//(*fCalorimeterCollection)[previousHitHistory[currentCalorimeterCopy][currentCellCopy]]->AddEdep(edep);
		        	//(*fCalorimeterCollection)[previousHitHistory[currentCalorimeterCopy][currentCellCopy]]->AddEdep(edep);
				
				(*fCalorimeterCollection)[fCellID[currentCalorimeterCopy][currentCellCopy]]->AddEdep(edep);
				(*fCalorimeterCollection)[fCellID[currentCalorimeterCopy][currentCellCopy]]->AddInteraction();
				
				//G4cout<<"Adding hits to calorimeter "<<G4endl;
    			} 
  	
		else 
			{        
        			//adding new hit to scintillator
        			CalorimeterHit* newHit = new CalorimeterHit();
        				newHit->SetEdep(edep);
        				newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
        				newHit->SetTrackPDG(aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
        				newHit->SetProcessName(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
        				newHit->SetInteractionNumber();
        				newHit->SetPosition(aStep->GetPostStepPoint()->GetPosition());
        				newHit->SetTime(currentTime);
					newHit->SetCellID(theTouchable->GetReplicaNumber(0),theTouchable->GetReplicaNumber(2)); //new added
					
					//G4cout<<"cellID calSD= "<<(theTouchable->GetReplicaNumber(0),theTouchable->GetReplicaNumber(2))<<G4endl;
        	
					newHit->SetCalorimeterID(theTouchable->GetReplicaNumber(2));
					newHit->SetPolarizationIn(aStep->GetPreStepPoint()->GetPolarization());
        				newHit->SetPolarizationOut(aStep->GetPostStepPoint()->GetPolarization());
        				newHit->SetMomentumIn(aStep->GetPreStepPoint()->GetMomentum());
        				newHit->SetMomentumOut(aStep->GetPostStepPoint()->GetMomentum());
					
					G4int id = fCalorimeterCollection->insert(newHit);
				//G4cout<<"previousHitHistory"<<previousHitHistory[currentCalorimeterCopy][currentCellCopy]<<G4endl;
				//previousHitHistory[currentCalorimeterCopy][currentCellCopy] = id-1;
				
				fCellID[currentCalorimeterCopy][currentCellCopy] = id-1;
				
				//G4cout<<"checking calorimeter copy "<<currentCalorimeterCopy<<"  id-1 = "<<id-1<<G4endl;
				//previousHitTimeHistory[currentCalorimeterCopy][currentCellCopy]= currentTime;
		
				//G4int icell = fCalorimeterCollection->insert(newHit ); 	
                		//G4cout<<"icell= "<<icell<<G4endl;	
				//CellID[currentCalorimeterCopy] = icell - 1;
    				//if(verboseLevel>0)
    				//{ G4cout << " New Calorimeter Hit on CellID " << currentCalorimeterCopy<< G4endl; }        	
			}
		
		/*G4int id = fChamberCollection->insert(newHit);
        	previousHitHistory[currentChamberCopy] = id-1;
                G4cout<<"checking chambercopy "<<currentChamberCopy<<"  id-1 = "<<id-1<<G4endl;
        	previousHitTimeHistory[currentChamberCopy]= currentTime;
	
		{
    			CalorimeterHit* calHit = new ExN05CalorimeterHit(physVol->GetLogicalVolume());
    				calHit->SetEdep( edep );
				calHit->SetRot(aTrans.NetRotation());
				calHit->SetRot(aTrans.NetRotation());    			
			G4AffineTransform aTrans = hist->GetHistory()->GetTopTransform();
    			aTrans.Invert();
    			G4int icell = CalCollection->insert( calHit );
    			CellID[copyID] = icell - 1;
    		if(verboseLevel>0)
    			{ 
				G4cout << " New Calorimeter Hit on CellID " << copyID << G4endl; }
  			}
  		else
  			{ 
    				(*CalCollection)[CellID[copyID]]->AddEdep( edep );
    				if(verboseLevel>0)
    					{ 
						G4cout << " Energy added to CellID " << copyID << G4endl; }
  			}*/

  		G4cout<<" at the end of ::ProcessHits"<<G4endl;
  		return true;
	}

/*void CalorimeterSD::EndOfEvent(G4HCofThisEvent*HCE)
	{   
		G4cout<<" Endof Event CalorimeterSD"<<G4endl;
  		if(CaloHCID<0)
  		{ 
			CaloHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  			HCE->AddHitsCollection( CaloHCID, fCalorimeterCollection );
	}		

void ExN05CalorimeterSD::clear()
	{} 

void ExN05CalorimeterSD::DrawAll()
	{} 

void ExN05CalorimeterSD::PrintAll()
	{} */
