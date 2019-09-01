//scintillator hits class definition

#ifndef CalorimeterHit_h
#define CalorimeterHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"

class CalorimeterHit : public G4VHit
	{
  		public:
			//constructor & deconstructor
    			CalorimeterHit(); 				
   			virtual ~CalorimeterHit();
    		
			//member functions
			void SetEdep(G4double de)			{fEdep = de; }
    			void SetTime(G4double val)			{fTime = val;}
			void SetCalorimeterID(G4int i) 			{fCalorimeterID = i;}
			void SetCellID(G4int i, G4int j) 		{fCellID = i,j;}
    			void SetTrackID(G4int i) 			{fTrackID = i;}
    			void SetTrackPDG(G4int i) 			{fTrackPDG = i;}
    			void SetPosition(G4ThreeVector xyz) 		{fPos = xyz;}
    			void SetInteractionNumber() 			{fNumInteractions = 1;}
			void SetProcessName(G4String str) 		{fName = str;}
    			void AddInteraction() 				{fNumInteractions += 1;}
    			void AddEdep(G4double de) 			{fEdep += de;}
    			void SetPolarizationIn(G4ThreeVector xyz) 	{fPolarizationIn = xyz;}
    			void SetPolarizationOut(G4ThreeVector xyz) 	{fPolarizationOut = xyz;}
    			void SetMomentumIn(G4ThreeVector xyz)  		{fMomentumIn = xyz;}
    			void SetMomentumOut(G4ThreeVector xyz) 		{fMomentumOut = xyz;}
    			
			G4double GetEdep() 				{return fEdep;}
	    		G4double GetTime() 				{return fTime;}
			G4int GetCalorimeterID()		 	{return fCalorimeterID;}
			G4int GetCellID() 				{return fCellID;}
    			G4int GetTrackID() 				{return fTrackID;}
    			G4int GetTrackPDG() 				{return fTrackPDG;}
			G4ThreeVector GetPosition() 			{return fPos;}
			G4int GetNumInteractions() 			{return fNumInteractions;}
    			G4String GetProcessName() 			{return fName;}
    			G4ThreeVector GetPolarizationIn()  		{return fPolarizationIn;}
    			G4ThreeVector GetPolarizationOut() 		{return fPolarizationOut;}
    			G4ThreeVector GetMomentumIn()  			{return fPolarizationIn;}
    			G4ThreeVector GetMomentumOut() 			{return fPolarizationOut;}
    		
    		private:
			//data members
			G4double fEdep; 				//total energy deposited in the strip
    			G4double fTime; 				//interaction time
			G4int fCalorimeterID; 				//calorimeter number
			G4int fCellID; 					//cell number
			G4int fTrackID; 				//track identificator 
    			G4int fTrackPDG; 				//particle data group numbering for particles
    			G4ThreeVector fPos; 				//3D interaction position
    			G4int fNumInteractions; 			//counters for interaction classified as single hit
			G4String fName; 				//< process name
    			G4ThreeVector fPolarizationIn;  		//< polarization vector before interaction
    			G4ThreeVector fPolarizationOut; 		//< polarization vector after interaction
    			G4ThreeVector fMomentumIn;  			//< momentum vector before interaction
    			G4ThreeVector fMomentumOut; 			//< momentum vector after interaction
	};

		typedef G4THitsCollection<CalorimeterHit> CalorimeterHitsCollection;

#endif
