//chamber sensitive detector class file

#ifndef ChamberSD_h
#define ChamberSD_h 1

#include "ChamberHit.hh"

#include "G4VSensitiveDetector.hh"
//class G4Step;
//class G4HCofThisEvent;
//class G4TouchableHistory;
class ChamberSD : public G4VSensitiveDetector
	{
		public: 
			//constructor & deconstructor      
      			ChamberSD(G4String name);
      			virtual~ChamberSD();

			//member functions
      			virtual void Initialize(G4HCofThisEvent*HCE);
			//void EndOfEvent(G4HCofThisEvent*HCE);
      			//void clear();
      			//void DrawAll();
      			//void PrintAll();
        
  		private:
			const G4double timeIntervals = 0.08; // 80 ps
        		const G4int totchamber = 16; 
        		G4int previousHitHistory[16];
        		G4double previousHitTimeHistory[16];      
			ChamberHitsCollection* fChamberCollection;

		protected:
         		virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
	};
#endif

