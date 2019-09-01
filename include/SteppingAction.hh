//definition of class for each step of particle transport

#ifndef SteppingAction_h
#define SteppingAction_h 1

//geant4 includes
#include "G4UserSteppingAction.hh"

class SteppingAction: public G4UserSteppingAction
	{
    		public:
			//constructor & destructor
        		SteppingAction();
        		~SteppingAction();
	};

#endif
