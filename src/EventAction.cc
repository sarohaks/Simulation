
#include "EventAction.hh"
#include "DetectorHit.hh"
#include "ChamberHit.hh"
#include "Trajectory.hh"
#include "CalorimeterHit.hh"

#include "G4PrimaryParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4EmCalculator.hh"



EventAction::EventAction(HistoManager* histo)
     	:G4UserEventAction(), 
     	fChamberCollID(-1),
	fCalorimeterCollID(-1)
	//fCellCollID(-1)
	//fDetectorCollID(-1)
	
{
	fHisto = histo;
}

EventAction::~EventAction()
{
	
}


void EventAction::BeginOfEventAction(const G4Event*)
{
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
        //G4cout<<"BeginOfEvent fChamberCollID =  " << fChamberCollID <<" , fDetectorColID = "<<fDetectorCollID<<G4endl; 	

	//if(fChamberCollID<0||fDetectorCollID<0) 

	if(fChamberCollID<0 && fCalorimeterCollID<0)// && fCellCollID<0)
	{
	G4String colNam;
	//||fCalorimeterCollID<0||fChamberCollID<0)
	//fDetectorCollID= SDman->GetCollectionID(colNam="DetectorCollection");
	
  	fChamberCollID = SDman->GetCollectionID(colNam="ChamberCollection");
	fCalorimeterCollID = SDman->GetCollectionID(colNam="CalorimeterCollection");

        //G4cout<<fChamberCollID<<" ,  "<<fDetectorCollID<<G4endl;
	G4cout<<fChamberCollID<<G4endl;
	G4cout<<fCalorimeterCollID<<G4endl;
	
	}
   
}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{

	if(anEvent->GetNumberOfPrimaryVertex()==0) return;
	
	G4int event_id = anEvent->GetEventID();
   	if (event_id % 10000 == 0)
	{
         printf ("Processed %i events \n", event_id);
     	}
      
      	G4cout << "Starting Event: " << anEvent->GetEventID() << G4endl ;
	
	G4TrajectoryContainer* trajectoryContainer = anEvent->GetTrajectoryContainer();
   	G4int trackNum = 0;
   		
	if(trajectoryContainer) 
		trackNum = trajectoryContainer->entries();
	for (G4int i=0; i<trackNum; i++)
     	{
         	Trajectory* trajectory = (Trajectory*)((*( anEvent->GetTrajectoryContainer()))[i]); 
         	fHisto->GetTrackTree()->Fill(event_id,trajectory);
         	fHisto->FillTrk();
	}

	//G4cout<< " Event " << anEvent->GetEventID() << G4endl;
  	
	//if(fChamberCollID<0||fDetectorCollID<0) return;
  	

	G4HCofThisEvent * HCE = anEvent->GetHCofThisEvent();

        G4cout<<"HCE true/false = "<<HCE<<G4endl;

	//DetectorHitsCollection* DetHC = 0;
  	ChamberHitsCollection* ChamberHC = 0;
	CalorimeterHitsCollection* CalorimeterHC = 0;
	
  	
	if(HCE)
    {
      		//DetHC = (DetectorHitsCollection*)(HCE->GetHC(fDetectorCollID));
		//int n_hit = DetHC->entries();
		ChamberHC = (ChamberHitsCollection*)(HCE->GetHC(fChamberCollID));
		CalorimeterHC = (CalorimeterHitsCollection*)(HCE->GetHC(fCalorimeterCollID));
	}

	if(ChamberHC)
	{

		//ChamberHC = (ChamberHitsCollection*)(HCE->GetHC(fChamberCollID));
		int n_hit = ChamberHC->entries();
                G4cout<<" +++++ n_hits of chamber +++++  = "<<ChamberHC->entries()<<G4endl;
		for (int i=0; i<n_hit; i++)
        	{
           		ChamberHit*  hit = (ChamberHit*)ChamberHC->GetHit(i);
           		fHisto->GetChamberBox()->Fill(n_hit,i,event_id,hit);
           		fHisto->FillChamberBox();
      		}
	}
	if(CalorimeterHC)
	{

      		int n_hit = CalorimeterHC->entries();
		G4cout<<" +++++ n_hits of calorimeter +++++  = "<<CalorimeterHC->entries()<<G4endl;
		for (int i=0; i<n_hit; i++)
        	{
           		CalorimeterHit*  hit = (CalorimeterHit*)CalorimeterHC->GetHit(i);
           		fHisto->GetCalorimeterBox()->Fill(n_hit,i,event_id,hit);
           		fHisto->FillCalorimeterBox();
      		}

		

   	}
    
	
	/*if(DetHC)
   	{
      		int n_hit = DetHC->entries();
      		G4cout << "     " << n_hit<< " hits are stored in DetectorHitsCollection." << G4endl;
      		G4double totE = 0;
      		for(int i=0;i<n_hit;i++)
        		{ totE += (*DetHC)[i]->GetEdep(); }
	
		for (int i=0; i<n_hit; i++)
        	{
           		DetectorHit*  hit = (DetectorHit*)DetHC->GetHit(i);
           		fHisto->GetDetectorBlock()->Fill(n_hit,i,event_id,hit);
           		fHisto->FillDetector();
        }
      		
		G4cout << "     Total energy deposition in Detector unit : "<< totE / keV << " (KeV)" << G4endl;
    	}
  	
	if(CaloHC)
   	{
      		int n_hit = CaloHC->entries();
      		G4cout << "     " << n_hit<< " hits are stored in CalorimeterHitsCollection." << G4endl;
      		G4double totE = 0;
      		for(int i=0;i<n_hit;i++)
        		{ totE += (*CaloHC)[i]->GetEdep(); }
      		
		//G4cout << "     Total energy deposition in Calorimeter unit : "<< totE / keV << " (KeV)" << G4endl;
    	}

	if(ChamberHC)
    	{
      		int n_hit = ChamberHC->entries();
      		G4cout << "     " << n_hit<< " hits are stored in ChamberHitsCollection." << G4endl;
      		G4double totE = 0;
      		for(int i=0;i<n_hit;i++)
        		{ totE += (*ChamberHC)[i]->GetEdep(); }
		for (int i=0; i<n_hit; i++)
        	{
           		ChamberHit*  hit = (ChamberHit*)ChamberHC->GetHit(i);
           		fHisto->GetChamberBox()->Fill(n_hit,i,event_id,hit);
           		fHisto->FillChamberBox();
      		}
		G4cout << "     Total energy deposition in Chamber unit : "<< totE / keV << " (keV)" << G4endl;
    	}*/


	/*G4TrajectoryContainer* trajectoryContainer = anEvent->GetTrajectoryContainer();
   	G4int trackNum = 0;
   		
	if(trajectoryContainer) 
		trackNum = trajectoryContainer->entries();

	for (G4int i=0; i<trackNum; i++)
     	{
         	Trajectory* trajectory = (Trajectory*)((*( anEvent->GetTrajectoryContainer()))[i]); 
         	fHisto->GetTrackTree()->Fill(event_id,trajectory);
         	fHisto->FillTrk();
	}*/

	



	
}

