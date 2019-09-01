#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4UI_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"

#include "Randomize.hh"
#include "time.h"
#include <G4INCLRandom.hh>

//int main()
int main(int argc, char** argv)
{

	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
    G4long seed = time(NULL);
    CLHEP::HepRandom::setTheSeed(seed);
    long seeds[2];
    time_t systime = time(NULL);
    seeds[0] = (long) systime;
    seeds[1] = (long) (systime * G4UniformRand());
    G4Random::setTheSeeds(seeds);




	// construct the default run manager
	G4RunManager* runManager = new G4RunManager;
	
        // set mandatory initialization classes
	runManager->SetUserInitialization(new DetectorConstruction);
	runManager->SetUserInitialization(new PhysicsList);
	runManager->SetUserInitialization(new ActionInitialization);
	// set mandatory user action class
	//runManager->SetUserAction(new PrimaryGeneratorAction);

	// initialize G4 kernel
	runManager->Initialize();
	// Get the pointer to the User Interface manager

	#ifdef G4VIS_USE
   	G4VisManager* visManager = new G4VisExecutive;
   	visManager->Initialize();
	#endif    

	G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
     if ( argc == 1 ) {
	
        // interactive mode : define UI session
	#ifdef G4UI_USE

	G4UIExecutive* ui = new G4UIExecutive(argc, argv);
	#endif
	#ifdef G4VIS_USE
      	UImanager->ApplyCommand("/control/execute init_vis.mac");     
	#endif
	
	ui->SessionStart();
	delete ui;
	
	
	#ifdef G4VIS_USE
      	delete visManager;
	#endif     

	
	}

   else {
	
	// batch mode
	G4String command = "/control/execute ";
	G4String fileName = argv[1];
	UImanager->ApplyCommand(command+fileName);
	}

	// job termination
 delete runManager;
 
 return 0;
}
