//definition class for tracking 

#ifndef TrackTree_h
#define TrackTree_h

//user defined header file include
#include "Trajectory.hh"

//geant4 & root includes
#include "globals.hh"
#include "TObject.h"
#include "G4ThreeVector.hh"
#include "G4Trajectory.hh"
#include "TVector3.h" 
#include "G4SystemOfUnits.hh"

//standard includes
#include <vector>

class TrackTree : public TObject 
	{
    		public:
			//constructor & destructor
        		TrackTree();
        		~TrackTree();
        	
			//member functions
			void Clean();
        		void Fill(G4int id, Trajectory* traj);
		
	    	private:
			//data members
     			G4int		fEventID;
     			G4int           fTrackID;                           
     			G4int           fParentID; 
			G4int           fMaterial; 
			G4int           fPDGEncoding;   
			G4double        fTime;                    		                  
     			G4double        fPDGCharge;                        
     			G4String        fParticleName;                     
     			TVector3        fVtxMomentum;                 
     			TVector3        fVtxPosition;        
     			
     		//class definition 
      		ClassDef(TrackTree,1)
	};

#endif
