#ifndef HistoManager_h 
#define HistoManager_h 1 

//user defined header file include
#include "TrackTree.hh"
#include "EventInfo.hh"
#include "ChamberBox.hh"
#include "CalorimeterBox.hh"

//geant4 & root includes
#include "globals.hh"
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>

const G4int MaxHisto = 6;

class TFile;
class TTree;
class HistoManager
	{
    		public:
			//constructor & destructor
        		HistoManager();
        		~HistoManager();
		
			//member functions
        		void Book(); 					//call once; book all trees and histograms
        		void Save(); 					//call once; save all trees and histograms
        		void FillTrk(); 				//translate TrackTree.cc into tree
        		//void FillDetector(); 				//translate DetectorBlock.cc into tree
        		void FillEventInfo();
			void FillChamberBox();
			void FillCalorimeterBox();
        
			//function pointer to user defined information class
       			TrackTree* GetTrackTree() const {return fTrackTree;}
       			EventInfo* GetEventInfo() const {return fEventInfo;}
			ChamberBox* GetChamberBox() const {return fChamberBox;}
			CalorimeterBox* GetCalorimeterBox() const {return fCalorimeterBox;}
			//DetectorBlock* GetDetectorBlock() const {return fDetectorBlock;}
    	
		private:
			//pointer to root classes
	        	TFile*   		fRootFile;
        		TH1D*    		fHisto[MaxHisto];
        		TTree*   		fTree1; 
        		TTree*   		fTree2; 
        		TTree*   		fTree3; 
			TTree*   		fTree4; 
        		TBranch* 		fBranchTrk;
        		TBranch* 		fBranchEventInfo;
			TBranch* 		fBranchChamberBox;
			TBranch* 		fBranchCalorimeterBox;
		
			//pointer to user defined classes
        		TrackTree* 		fTrackTree;
        		EventInfo*   		fEventInfo;
			ChamberBox*		fChamberBox;
			CalorimeterBox*		fCalorimeterBox;
			
			//DetectorBlock* 		fDetectorBlock;
        		//std::unique_ptr<Event> fEvent {new Event()};
	};
	
#endif
