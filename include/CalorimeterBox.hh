//definion of calorimeterbox root-class for information handling 

#ifndef CalorimeterBox_h
#define CalorimeterBox_h

//user defined header file include
#include "CalorimeterHit.hh"

//geant4 & root includes
#include "globals.hh"
#include "TObject.h"
#include "G4ThreeVector.hh"
#include "TVector3.h"

//standard includes
#include <vector> 

//brief class directly written into ROOT files; translates  

class CalorimeterBox : public TObject
	{
    		public:
			//constructor & destructor           		
			CalorimeterBox();
        		~CalorimeterBox();

			//member functions
        		void Clean();
        		void Fill(G4int hitTNo, G4int hitNo, G4int iD, CalorimeterHit* hit);
        		
			G4double GetEdep() 				{return eDep;}
			G4double GetTime() 				{return time;}
        		G4int GetCalorimeterID() 			{return calorimeterID;}
			G4int GetCellID() 				{return cellID;}
        		G4int GetTotHitNumber() 			{return hitTotNumber;}
        		G4int GetHitNumber() 				{return hitNumber;}
        		TVector3 GetPosition() 				{return position;}
        		
    		private:
			//data members  
			G4double eDep;					//energy deposited by a hit
        		G4double time;					//global time      		
			G4int numInteractions;				//number of interaction by an event
        		G4int calorimeterID;				//calorimeter number ID
			G4int cellID;					//cell number in calorimeter
        		G4int hitTotNumber;				//total hit by an event
        		G4int hitNumber;				//hit number
        		G4int evtID;					//event number ID
			G4int trackID;					//track number ID by hit
        		G4int trackPDGencoding;				//PDG number ID
        		TVector3 position;				//position
        		TVector3 polarizationIn;			//polarization of incoming particle before hit
        		TVector3 polarizationOut;			//polarization of outgoing particle after hit
        		TVector3 momentumIn;				//momentum of incoming particle before hit
        		TVector3 momentumOut;				//momentum of outgoing particle after hit
		
		//class definition
		ClassDef(CalorimeterBox,1)     
	};

#endif
