#include "CalorimeterBox.hh"
//#include "TranslateInteraction.hh"

CalorimeterBox::CalorimeterBox()
     :evtID(0), calorimeterID(0), cellID(0),  trackID(-1), eDep(0), time(0)
	
{
}

CalorimeterBox::~CalorimeterBox()
{}

void CalorimeterBox::Clean()
{}

void CalorimeterBox::Fill(G4int hitTNo, G4int hitNo, G4int iD, CalorimeterHit* hit)
{
    	hitTotNumber = hitTNo;
    	hitNumber = hitNo+1;
    	evtID = iD;
    	calorimeterID = hit->GetCalorimeterID();
	cellID = hit->GetCellID();
    	trackID = hit->GetTrackID();
    	trackPDGencoding = hit->GetTrackPDG();

    	eDep = hit->GetEdep();
    	time = hit->GetTime();
    	position.SetX(hit->GetPosition().getX());
    	position.SetY(hit->GetPosition().getY());
    	position.SetZ(hit->GetPosition().getZ());
	
    	polarizationIn.SetX(hit->GetPolarizationIn().getX());
    	polarizationIn.SetY(hit->GetPolarizationIn().getY());
    	polarizationIn.SetZ(hit->GetPolarizationIn().getZ());

    	polarizationOut.SetX(hit->GetPolarizationOut().getX());
    	polarizationOut.SetY(hit->GetPolarizationOut().getY());
    	polarizationOut.SetZ(hit->GetPolarizationOut().getZ());

    	momentumIn.SetX(hit->GetMomentumIn().getX());
    	momentumIn.SetY(hit->GetMomentumIn().getY());
    	momentumIn.SetZ(hit->GetMomentumIn().getZ());

    	momentumOut.SetX(hit->GetMomentumOut().getX());
    	momentumOut.SetY(hit->GetMomentumOut().getY());
    	momentumOut.SetZ(hit->GetMomentumOut().getZ());

    	numInteractions = hit->GetNumInteractions();

    	G4cout << hit->GetProcessName() << " "<< eDep << " " << time << " " << numInteractions  << G4endl;
    	//intType = TranslateInteraction(hit->GetProcessName());

}
