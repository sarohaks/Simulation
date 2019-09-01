//definition of class for trajectory of particle transport

#ifndef Trajectory_h
#define Trajectory_h 1 

//geant4 & root includes
#include "G4VTrajectory.hh"
#include "globals.hh" 
#include "G4Track.hh" 
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"

typedef std::vector<G4VTrajectoryPoint*> TrajectoryPointContainer;

class Trajectory : public G4VTrajectory 
	{
    		public:
			//constructor & destructor 
        		Trajectory(const G4Track* aTrack); 
        		virtual ~Trajectory();

			//member functions
        		virtual void MergeTrajectory(G4VTrajectory* secondTrajectory);
        		virtual void AppendStep(const G4Step* aStep);
	     		//virtual void DrawTrajectory() const;
        		virtual G4int GetTrackID() const { return fTrackID; } 
        		virtual G4int GetParentID() const { return fParentID; }
        		virtual G4String GetParticleName() const { return fParticleName; } 
        		virtual G4double GetCharge() const { return fPDGCharge; } 
        		virtual G4int GetPDGEncoding() const { return fPDGEncoding; } 
        		virtual G4ThreeVector GetInitialMomentum() const { return fMomentum;}
        		virtual G4ThreeVector GetVertexPosition() const { return fVertexPosition;}
        		virtual int GetPointEntries() const { return fPositionRecord->size();}
        		virtual G4VTrajectoryPoint* GetPoint(G4int i) const { return (*fPositionRecord)[i]; }

		        G4double GetTime() const { return fGlobalTime; } 

    		private:
     			//data members
     			G4int  		fTrackID;                           
     			G4int           fParentID;                     
     			G4int           fTrackStatus;                   
     			G4int           fPDGEncoding;                               
     			G4double        fPDGCharge;                        
     			G4double        fGlobalTime;  
			G4String        fParticleName;                  
     			G4ThreeVector   fMomentum;                          
     			G4ThreeVector   fVertexPosition;                    
     			
			//pointer to trajectory point container			
			TrajectoryPointContainer* fPositionRecord;
	
			//pointer to g4particle definition
			G4ParticleDefinition*        fParticleDefinition;  
	};

#endif
