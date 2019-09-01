#ifndef EventAction_h
#define EventAction_h

#include "HistoManager.hh"
#include "G4UserEventAction.hh"
#include "globals.hh" 

#include <memory>

/**
 * \class EventAction
 * \brief class managing events 
 *
 * Here also one can reach for information
 * after propagation of all tracks in detector.
 * One ned to be shue to store all trajectories while propagating (hidden in standard usage)
 */
class EventAction : public G4UserEventAction
{
    	public:
        	EventAction(HistoManager* histo); 
        	virtual ~EventAction();
        	virtual void BeginOfEventAction(const G4Event*);
        	virtual void EndOfEventAction(const G4Event* anEvent);

    	private:
		HistoManager* fHisto; 
        	//G4int fDetectorCollID ;
		G4int fChamberCollID ;
		G4int fCalorimeterCollID ;
		//G4int fCellCollID;
};

#endif
