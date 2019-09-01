//material extension class definition for ennihilation

#ifndef MaterialExtension_h
#define MaterialExtension_h

//geant4 includes
#include "G4VMaterialExtension.hh"
#include "G4Material.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//brief extended material keeps information about 2g/3g creation fraction

const G4double foPsVaccum = 0.125*ns;

//class MaterialExtension : public G4VMaterialExtension
class MaterialExtension : public G4Material
	{
    		public:
			//constructor & destructor 
      			MaterialExtension(const G4String& name, const G4Material* baseMaterial);
			~MaterialExtension();
      		
			//member functions
      			void SetoPsLifetime(G4double);
			//void Set3gProbability(G4double);
			void Set2gProbability(G4double);
			//G4double Get3gFraction(); 
			G4double Get2gFraction(); 
		
			G4Material* GetMaterial() {return fMaterial;};
      			G4bool IsTarget() {return fTarget;};
      			void AllowsAnnihilations(G4bool tf){ fTarget = tf;};
			void Print() const {;};
      			G4bool IsExtended() const { return true; }
	
		private:
			//data members    		
      			G4bool fTarget;
			//G4double f3gFraction; ///<  3g/2g events fraction 
			G4double f2gFraction;
      			G4double foPsPobability; 
      			G4double foPslifetime;

			//pointer to g4material
			G4Material* fMaterial;
	};

#endif
