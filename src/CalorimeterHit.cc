
#include "CalorimeterHit.hh"


CalorimeterHit::CalorimeterHit()
    : G4VHit(), fCalorimeterID(0), fTrackID(-1), fEdep(0.0), fTime(0), fPos(0)
	
{G4cout<<"calling CalorimeterHit"<<G4endl;}

CalorimeterHit::~CalorimeterHit()
{
G4cout<<"cellID="<<fCellID<<G4endl;
}

