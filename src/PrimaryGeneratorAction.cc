//action required to be done after primary generation

//user defined header file include
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

//geant4 includes 
#include "G4PrimaryVertex.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(HistoManager* histo) 
		:G4VUserPrimaryGeneratorAction(), fPrimaryGenerator(0), fHisto(histo)
	{
    		fPrimaryGenerator = new PrimaryGenerator();
	}

PrimaryGeneratorAction::~PrimaryGeneratorAction() 
	{
    		delete fPrimaryGenerator;
	}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) 
	{
   		fPrimaryGenerator->GeneratePrimaryVertex(event);
		//G4int numPrimVtx = event->GetNumberOfPrimaryVertex(); 
		//for (int i=0; i<numPrimVtx; i++)
       		
		int i=0;    
        	G4PrimaryVertex* vtx = event->GetPrimaryVertex(i);
        		fHisto->GetEventInfo()->FillEventInfo( event->GetEventID(), vtx->GetX0(), vtx->GetY0(), vtx->GetZ0(), vtx->GetT0());    
        		fHisto->FillEventInfo();
	}



