//Start the PrimaryGeneratorAction, EventAction, RunAction, TrackingAction & SteppingAction 

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "HistoManager.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
     		:G4VUserActionInitialization()
    	{}

ActionInitialization::~ActionInitialization()
     	{}

void ActionInitialization::BuildForMaster() const
    	{;}

void ActionInitialization::Build() const
     	{
     		HistoManager* histo = new HistoManager();
    	       
		//user action classes mandatory to initialize 
               	SetUserAction(new PrimaryGeneratorAction(histo));
    	       	SetUserAction(new RunAction(histo));
    	       	SetUserAction(new EventAction(histo));
		
		//user action classes not mandatory to initialize
    	       	SetUserAction(new TrackingAction);
    	       	SetUserAction(new SteppingAction);
  	}

