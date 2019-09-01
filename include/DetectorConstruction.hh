//detector construction class definition

#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

//user defined header file include
#include "MaterialExtension.hh"

//geant4 includes
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4Trd.hh"
#include "G4Box.hh"
#include "globals.hh"

//standard includes
#include <list>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h> 




class G4LogicalVolume ;
class G4PhysicalVolume ;
class DetectorConstruction : public G4VUserDetectorConstruction
	{
		public :
      			//constructor & destructor
      			DetectorConstruction() ;
      			~DetectorConstruction() ;
			//member functions
			void DefineMaterials() ;
			G4VPhysicalVolume* Construct() ;
			G4Box* ChamberBox(G4String name, G4double length, G4double breadth, G4double width) ;
			void PlaceGeometry(G4RotationMatrix *pRot, G4ThreeVector tlate, G4LogicalVolume *pMotherLogical) ; 
			void ConstructSDandField();

			//data members
			G4double	   	chamberBox_hx;
			G4double  	   	chamberBox_hy;
			G4double           	chamberBox_hz;
			G4double           	calorimeter_hz;
			G4int		   	nX;
			G4int 		   	nY;
			G4int		   	n_detector;
			G4int		   	n_cell;
 		private :
			//G4Material*        	fEmptyMat;      		
			//G4Material*        	fG10Mat;
			//G4Material*        	fGasMat;
			//G4Material*        	fInsulationMat;
      			//G4Material*        	fFoilMat;
      			//G4Material*        	fSciMat;
			
			//pointer to material extension
			MaterialExtension* 	SciMat; 
    			MaterialExtension* 	EmptyMat; 
    			MaterialExtension* 	G10Mat;    
    			MaterialExtension* 	InsulationMat;
			MaterialExtension* 	FoilMat;
    			MaterialExtension* 	GasMat;
			
			//pointer to production cut				
			G4ProductionCuts*  	fGasDetectorCuts;
			
			//boolean checks for overlapping
			G4bool             	fCheckOverlaps;
			
			//G4LogicalVolume*   	g10_1Log;
     			G4LogicalVolume*   	gasGap1DLog;
			G4LogicalVolume*   	gasGap2T1Log;
			G4LogicalVolume*   	gasGap3T2Log;
			G4LogicalVolume*   	gasGap4ILog;
			//G4LogicalVolume*   	g10_2Log;
			G4LogicalVolume*   	crystalLog;
 			
			//chamber box vector collection
			std::vector<G4Box*>           chamberBoxCollection ;
      			std::vector<G4LogicalVolume*> chamberBoxLogCollection ;
	};	
#endif
