//scintillation sensitive detector class file

#ifndef CalorimeterSD_h
#define CalorimeterSD_h 1

//user defined header file include
#include "CalorimeterHit.hh"

//geant4 includes
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class CalorimeterSD : public G4VSensitiveDetector
	{
		public:
			//constructor & destructor
      			CalorimeterSD(G4String name);
      			virtual~CalorimeterSD();
			
			//member functions
      			virtual void Initialize(G4HCofThisEvent*HCE);
      			//void EndOfEvent(G4HCofThisEvent*HCE);
      			//void clear();
      			//void DrawAll();
      			//void PrintAll();
 			
			//data members
			G4int currentCalorimeterCopy;
  		
		private:
			//const G4double timeIntervals = 0.08; // 80 ps
        		const G4int totcal = 16; 
			const G4int totcell = 100;
        		//G4int previousHitHistory[16][100];
       			//G4double previousHitTimeHistory[16][100]; 
			//G4int lastHitHistory[100];
        		//G4double lastHitTimeHistory[100];	

			int fCellID[16][100];
			
			//defining pointer to calorimeter collection
			CalorimeterHitsCollection* fCalorimeterCollection;

		protected:
         		virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
	};
	
#endif

