//information of events class definition

#ifndef EventInfo_h
#define EventInfo_h 1

//geant4 & root includes
#include "TObject.h"
#include "TVector3.h"
#include "globals.hh"

class EventInfo : public TObject
	{
    		public:
        		//constructor & destructor
			EventInfo();
        		~EventInfo();
        		
			//member functions			
			void FillEventInfo(G4double id, G4double x, G4double y, G4double z, G4double t);
		
		private:
			//data members        		
			G4int 		fEventId;
        		G4double 	fX;     
        		G4double 	fY;     
        		G4double 	fZ;
        		G4double 	fTime;
        
		//class definition   
      		ClassDef(EventInfo,1)
	};

#endif
