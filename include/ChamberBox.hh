//definion of chamberbox root-class for information handling

#ifndef ChamberBox_h
#define ChamberBox_h

//user defined header file include
#include "ChamberHit.hh"

//geant4 & root includes
#include "globals.hh"
#include "TObject.h"
#include "G4ThreeVector.hh"
#include "TVector3.h"
#include "PrimaryGenerator.hh"
#include "G4VUserPrimaryParticleInformation.hh"

//standard includes
#include <vector> 

//brief class directly written into ROOT files; translates  
 
class ChamberBox : public TObject
	{
    	public:
			//constructor & destructor        		
			ChamberBox();
        	~ChamberBox();
        	
			//member functions
			void Clean();
        	void Fill(G4int hitTNo, G4int hitNo, G4int iD, ChamberHit* hit);
        		
			G4double GetEdep() 					{return eDep;}
			G4double GetTime() 					{return time;}
        	G4int GetChamberID() 				{return chamberID;}
			G4int GetChamberGapID() 			{return chamberGapID;}
        	G4int GetTotHitNumber() 			{return hitTotNumber;}
        	G4int GetHitNumber() 				{return hitNumber;}
			//G4String GetProcessName()    		{return processName;}
			//G4VUserPrimaryParticleInformation* GetParticleInfo()             {return particleInfo;}
        	TVector3 GetPositon() 				{return position;}
			TVector3 GetPolarizationIn() 		{return polarizationIn;}
			TVector3 GetPolarizationOut() 		{return polarizationOut;}
			TVector3 GetMomentumIn() 			{return momentumIn;}
			TVector3 GetMomentumOut() 			{return momentumIn;}
				
    	private:
			//data members
			G4double eDep;						//energy deposited by a hit
        	G4double time;						//global time      		
			G4int numInteractions;				//number of interaction by an event        		
			G4int chamberID;					//chamber number ID
			G4int chamberGapID;					//chamber gap number ID
			G4int hitTotNumber;					//total hit by an event
        	G4int hitNumber;				 	//hit number
        	G4int evtID;						//event number ID
        	G4int trackID;						//track number ID by hit
        	G4int trackPDGencoding;				//PDG number ID
        	//G4String processName;
        	//G4VUserPrimaryParticleInformation* particleInfo;
			TVector3 position;					//position
        	TVector3 polarizationIn;			//polarization of incoming particle before hit
        	TVector3 polarizationOut;			//polarization of outgoing particle after hit
        	TVector3 momentumIn;				//momentum of incoming particle before hit
        	TVector3 momentumOut;				//momentum of outgoing particle after hit        		

		//class definition
    	ClassDef(ChamberBox,1)     
	};

#endif
