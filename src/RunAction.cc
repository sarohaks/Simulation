//action to be done for each run

//user defined header file include
#include "RunAction.hh"

//geant4 includes
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction(HistoManager* histo)
    		:G4UserRunAction(), fHistoManager(histo)
	{  
		G4cout<<"Entering Run Action"<<G4endl;
	}

RunAction::~RunAction()
	{}

void RunAction::BeginOfRunAction(const G4Run*run)
	{
    		fHistoManager->Book();
	}

void RunAction::EndOfRunAction(const G4Run*run)
	{
     		fHistoManager->Save();
	}

