//information from each evnet filled in various trees

//user defined header file include
#include "HistoManager.hh"

//geant4 includes
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//standard includes
#include <vector>

//importing classes
ClassImp(TrackTree)
ClassImp(EventInfo)
ClassImp(ChamberBox)
ClassImp(CalorimeterBox)

HistoManager::HistoManager()
	{
    		fTrackTree = new TrackTree();
    		fEventInfo = new EventInfo();
		fChamberBox = new ChamberBox();
		fCalorimeterBox = new CalorimeterBox();
	}

HistoManager::~HistoManager()
	{}

void HistoManager::Book()
	{
   		G4String fileName = "qpet.root";
    		fRootFile = new TFile(fileName,"RECREATE");  
    		
		if (! fRootFile)
			{
				G4cout << " HistoManager::Book :"<< " problem creating the ROOT TFile "<< G4endl;   
        			return;
			} 

    		Int_t bufsize=100000;     //32000 old
    		Int_t splitlevel=2;

    		//histogram
    		//fHisto[0] = new TH1D("EAbs", "Edep in detector (keV)", 100, 0., 511*CLHEP::keV);  
		
		//tracktree filling in root file
    		fTree1 = new TTree("TTrack", "Tree keeps output from Geant simulation", splitlevel);
    		fTree1->SetAutoSave(1000000000); // autosave when 1 Gbyte written
    		fBranchTrk = fTree1->Branch("trackTree", &fTrackTree, bufsize, splitlevel);
	
		//event information filling in root file
    		fTree2 = new TTree("EventInfo", "Tree keeps output from Geant simulation");
    		fTree2->SetAutoSave(1000000000); // autosave when 1 Gbyte written
    		fBranchEventInfo = fTree2->Branch("eventInfo", &fEventInfo, bufsize, splitlevel);
	
		//chamber information filling in root file
		fTree3 = new TTree("ChamberBox", "Tree keeps output from Geant simulation");
    		fTree3->SetAutoSave(1000000000); // autosave when 1 Gbyte written
    		fBranchChamberBox = fTree3->Branch("chamberBox", &fChamberBox, bufsize, splitlevel);
	
		//calorimeter information filling in root file
		fTree4 = new TTree("CalorimeterBox", "Tree keeps output from Geant simulation");
    		fTree4->SetAutoSave(1000000000); // autosave when 1 Gbyte written
    		fBranchCalorimeterBox = fTree4->Branch("calorimeterBox", &fCalorimeterBox, bufsize, splitlevel);
	}

void HistoManager::FillTrk()
	{
    		fTree1->Fill();
	}

void HistoManager::FillEventInfo()
	{
    		fTree2->Fill();
	}

void HistoManager::FillChamberBox()
	{
    		fTree3->Fill();
	}

void HistoManager::FillCalorimeterBox()
	{
    		fTree4->Fill();
	}

void HistoManager::Save()
	{
    		//if (! fRootFile) return;
    		fRootFile->Write(); 
    		fRootFile->Close(); 
		G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
	}

