//defining run class for set of events

#ifndef RunAction_h 
#define RunAction_h 1

//user defined header file include
#include "HistoManager.hh"

//geant4 includes
#include "G4UserRunAction.hh"
#include "globals.hh"

//brief class manages the runs = set of events

class G4Run;
class RunAction : public G4UserRunAction 
	{
     		public:
			//constructor & destructor
         		RunAction(HistoManager*); 
         		virtual ~RunAction();

			//member functions
         		virtual void BeginOfRunAction(const G4Run*);
         		virtual void EndOfRunAction(const G4Run*);

     		private:
			//pointer to histo manager         		
			HistoManager* fHistoManager;
	};

#endif
