//information of event generated

//user defined header file include
#include "EventInfo.hh"

EventInfo::EventInfo()
	{
    		fEventId =-1; 							//initializing event number ID
    		fX=-1;								//initializing x-position
    		fY=-1;								//initializing y-position
    		fZ=-1;								//initializing z-position
    		fTime=-1;							//initializing time of generation
	}

void EventInfo::FillEventInfo(G4double id, G4double x, G4double y, G4double z, G4double t)
	{
		//setting information of event generated
    		fEventId = id;
    		fX= x;
    		fY= y;
    		fZ= z;
    		fTime= t;
	}

EventInfo::~EventInfo()
	{}
