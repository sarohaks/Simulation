//definition of class for each track of particle transport

#ifndef TrackingAction_h
#define TrackingAction_h 1

//geant4 includes
#include "G4UserTrackingAction.hh"

class TrackingAction : public G4UserTrackingAction 
	{
    		public:
			//constructor & destructor
        		TrackingAction() : G4UserTrackingAction() {}
        		virtual ~TrackingAction() {}
		
			//member functions
    			virtual void PreUserTrackingAction(const G4Track*);
        		virtual void PostUserTrackingAction(const G4Track*);
	};

#endif
