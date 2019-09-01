//information of hits in chamber  

#include "ChamberHit.hh"

ChamberHit::ChamberHit()
    		:G4VHit(), fChamberID(), fChamberGapID(), fTrackID(-1), fEdep(0.0), fTime(0), fPos(0)
	{
		//G4cout<<"calling ChamberHit"<<G4endl;
	}

ChamberHit::~ChamberHit()
	{}

