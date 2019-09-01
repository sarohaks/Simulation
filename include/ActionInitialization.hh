//action initialization class definition

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

//geant4 includes
#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization 
	{
    		public:
			//constructor & destructor             		
			ActionInitialization(); 
        		virtual ~ActionInitialization();
        		
			//member functions
			virtual void BuildForMaster() const; 
        		
			//functions called for each thread
			virtual void Build() const; 
	};

#endif
