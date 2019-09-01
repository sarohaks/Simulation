//chmaber box to fill the information of chamber inrteraction

//user defined header file include
#include "ChamberBox.hh"
#include "PrimaryGenerator.hh"
#include "G4VUserPrimaryParticleInformation.hh"

//#include "TranslateInteraction.hh"

ChamberBox::ChamberBox()
  		:evtID(0), chamberID(0), trackID(-1), eDep(0), time(0)
	{}

ChamberBox::~ChamberBox()
	{}

void ChamberBox::Clean()
	{}

void ChamberBox::Fill(G4int hitTNo, G4int hitNo, G4int iD, ChamberHit* hit)
	{
    	chamberID = hit->GetChamberID();							//fill chamber number ID
		chamberGapID = hit->GetChamberGapID();  					//fill chamber gap number ID
		//G4cout<<"chamberID................#####"<<chamberID<<G4endl;
		hitTotNumber = hitTNo;										//fill total hit of an event
    	hitNumber = hitNo+1;										//fill each hit of an event
    	evtID = iD;													//fill event number ID
    	trackID = hit->GetTrackID();								//fill track number ID
    	trackPDGencoding = hit->GetTrackPDG();						//fill PDG number ID
    	eDep = hit->GetEdep();										//fill energy deposit by a hit
    	time = hit->GetTime();										//fill time of hit
		numInteractions = hit->GetNumInteractions();				//fill number of interaction done by an event
		//processName = hit->GetProcessName();
		//particleInfo = hit->GetParticleInfo();

		//position information
    	position.SetX(hit->GetPosition().getX());
    	position.SetY(hit->GetPosition().getY());
    	position.SetZ(hit->GetPosition().getZ());
	
		//polarization of incoming particle before interaction
    	polarizationIn.SetX(hit->GetPolarizationIn().getX());
    	polarizationIn.SetY(hit->GetPolarizationIn().getY());
    	polarizationIn.SetZ(hit->GetPolarizationIn().getZ());

		//polarization of same outgoing particle after interaction
    	polarizationOut.SetX(hit->GetPolarizationOut().getX());
    	polarizationOut.SetY(hit->GetPolarizationOut().getY());
    	polarizationOut.SetZ(hit->GetPolarizationOut().getZ());

		//momentum of incoming particle before interaction 
    	momentumIn.SetX(hit->GetMomentumIn().getX());
    	momentumIn.SetY(hit->GetMomentumIn().getY());
    	momentumIn.SetZ(hit->GetMomentumIn().getZ());

		//momentum of same outging particle after interaction 
    	momentumOut.SetX(hit->GetMomentumOut().getX());
    	momentumOut.SetY(hit->GetMomentumOut().getY());
    	momentumOut.SetZ(hit->GetMomentumOut().getZ());

    		//G4cout << hit->GetProcessName() << " "<< eDep << " " << time << " " << numInteractions  << G4endl;
    		//intType = TranslateInteraction(hit->GetProcessName());
	}
