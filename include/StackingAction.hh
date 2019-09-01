//stacking action class definition

#ifndef StackingAction_H
#define StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "G4Step.hh"


class StackingActionMessenger;
class G4Navigator;
class G4Track;
class G4Step;
class StackingAction : public G4UserStackingAction 
	{
		public:
    			StackingAction();
    			virtual ~StackingAction();

 		public:
    			virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack, G4Step* aStep);
    			//virtual void NewStage();
    			//virtual void PrepareNewEvent();

		private:
    			G4bool killGammasFlag;

			G4Navigator* gNavigator; 

  		public:
    			inline void SetKillGammasFlag(G4bool val)     {killGammasFlag  = val;};
	};

#endif

