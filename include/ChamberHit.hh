//chamber hits class file 

#ifndef ChamberHit_h
#define ChamberHit_h 1

//geant4 includes
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"
#include "PrimaryGenerator.hh"
#include "G4VUserPrimaryParticleInformation.hh"

class ChamberHit : public G4VHit
	{
  		public:
			//constructor & destructor
    		ChamberHit(); 					
   			virtual ~ChamberHit();
			
			//member functions
    		void SetEdep(G4double de)						{fEdep = de; }
    		void SetTime(G4double val)						{fTime = val;}
			void SetChamberID(G4int i) 						{fChamberID = i;}
			void SetChamberGapID(G4int i) 					{fChamberGapID = i;}
			void SetTrackID(G4int i) 						{fTrackID = i;}
    		void SetTrackPDG(G4int i) 						{fTrackPDG = i;}
    		void SetPosition(G4ThreeVector xyz) 			{fPos = xyz;}
    		void SetInteractionNumber() 					{fNumInteractions = 1;}
			//void SetProcessName(G4String str) 				{fName = str;}
    		void AddInteraction() 							{fNumInteractions += 1;}
    		void AddEdep(G4double de) 						{fEdep += de;}
    		void SetPolarizationIn(G4ThreeVector xyz) 		{fPolarizationIn = xyz;}
    		void SetPolarizationOut(G4ThreeVector xyz) 		{fPolarizationOut = xyz;}
    		void SetMomentumIn(G4ThreeVector xyz)  			{fMomentumIn = xyz;}
    		void SetMomentumOut(G4ThreeVector xyz) 			{fMomentumOut = xyz;}
    		//void SetParticleInfo(G4VUserPrimaryParticleInformation* anInfo)			{fInfo = anInfo;}
    			
			G4double GetEdep() 								{return fEdep;}
    		G4double GetTime() 								{return fTime;}
			G4int GetChamberID() 							{return fChamberID;}
			G4int GetChamberGapID() 						{return fChamberGapID;}
    		G4int GetTrackID() 								{return fTrackID;}
    		G4int GetTrackPDG() 							{return fTrackPDG;}
    		G4ThreeVector GetPosition() 					{return fPos;}
    		G4int GetNumInteractions() 						{return fNumInteractions;}
			//G4String GetProcessName() 						{return fName;}	
    		G4ThreeVector GetPolarizationIn()  				{return fPolarizationIn;}
    		G4ThreeVector GetPolarizationOut() 				{return fPolarizationOut;}
    		G4ThreeVector GetMomentumIn()  					{return fPolarizationIn;}
    		G4ThreeVector GetMomentumOut() 					{return fPolarizationOut;}
    		//G4VUserPrimaryParticleInformation* GetParticleInfo()				 		{return fInfo;}
   		private:
			//data members    		
			G4double fEdep; 								//total energy deposited in the strip
    		G4double fTime; 								//interaction time			
			G4int fChamberID; 								//chamber number
			G4int fChamberGapID; 							//chamber gas gap number
			G4int fTrackID; 								//track identificator 
    		G4int fTrackPDG; 								//particle data group numbering for particles
    		G4ThreeVector fPos; 							//3D interaction position
    		G4int fNumInteractions; 						//counters for interaction classified as single hit
			//G4String fName; 								//process name    			
			G4ThreeVector fPolarizationIn;  				//polarization vector before interaction
	    	G4ThreeVector fPolarizationOut; 				//polarization vector after interaction
	    	G4ThreeVector fMomentumIn;  					//momentum vector before interaction
	    	G4ThreeVector fMomentumOut; 					//momentum vector after interaction
	    	//G4VUserPrimaryParticleInformation* fInfo;
	};

		typedef G4THitsCollection<ChamberHit> ChamberHitsCollection;

#endif
