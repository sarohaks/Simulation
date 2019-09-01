//definition of class for action required on primary generation

#ifndef PrimaryGeneratorAction_h 
#define PrimaryGeneratorAction_h 1

//user defined header file include
#include "PrimaryGenerator.hh"
#include "HistoManager.hh"

//geant4 includes
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4Event.hh"

//brief heart of simulated physics

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
	{
    		public:
			//constructor & destructor
        		PrimaryGeneratorAction(HistoManager* histo);
        		~PrimaryGeneratorAction();

			//member functions
        		virtual void GeneratePrimaries(G4Event*);
    		private:
			//pointer to primary generator & histo manager
       			PrimaryGenerator* fPrimaryGenerator; 
       			HistoManager* fHisto;
	};

#endif
