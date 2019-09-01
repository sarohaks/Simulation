//class definition for physics used

#ifndef PhysicsList_h
#define PhysicsList_h 1

//geant4 includes
#include "G4VModularPhysicsList.hh" 

//brief standard GEANT4 package is used for physics used G4EmLivermorePolarizedPhysics deals properly with polarized particles
 
class PhysicsList: public G4VModularPhysicsList
	{
    		public:
			//constructor & destructor     
    			PhysicsList();
    			virtual ~PhysicsList();
	};

#endif
