//Geaometry of the detector

//user defined headers include
#include "DetectorConstruction.hh"
#include "ChamberSD.hh"
#include "CalorimeterSD.hh"

//geant4 includes
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ProductionCuts.hh"
#include "G4ElementTable.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4GeometryManager.hh"
#include "G4Colour.hh"
	
DetectorConstruction::DetectorConstruction()	
		:fCheckOverlaps(0), fGasDetectorCuts(0) //fG10Mat(0), fGasMat(0), fEmptyMat(0), fInsulationMat(0), fFoilMat(0),
	{
       		G4double cut = 0.5*nm ;
   		fGasDetectorCuts = new G4ProductionCuts() ;
   		fGasDetectorCuts->SetProductionCut(cut,"gamma") ;
   		fGasDetectorCuts->SetProductionCut(cut,"e-") ;
   		fGasDetectorCuts->SetProductionCut(cut,"e+") ;
   		fGasDetectorCuts->SetProductionCut(cut,"proton");
	}

DetectorConstruction::~DetectorConstruction()
	{
		delete fGasDetectorCuts ;
	}

void DetectorConstruction::DefineMaterials()
	{
		G4NistManager* manager = G4NistManager::Instance();

		// define Elements
   		G4Element* elC  = manager->FindOrBuildElement(6);
   		G4Element* elF  = manager->FindOrBuildElement(9);
	
		//define Materials
		G4Material* H  = G4NistManager::Instance()->FindOrBuildMaterial("G4_H") ;
   		G4Material* C  = G4NistManager::Instance()->FindOrBuildMaterial("G4_C") ;
 		G4Material* O  = G4NistManager::Instance()->FindOrBuildMaterial("G4_O") ;
   		G4Material* Si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");

		//define G10 Materiel
		G4Material* G10Material = new G4Material("G10", 1.9*g/cm3, 4) ;
   			G10Material->AddMaterial(C,0.1323) ;
   			G10Material->AddMaterial(H,0.03257) ;
   			G10Material->AddMaterial(O,0.48316) ;
  			G10Material->AddMaterial(Si,0.35194) ;

		//define GEM foil material
		G4Material* Kapton = G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON");
		G4Material* Copper = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
   	
		// gases at STP conditions
   		G4Material* Argon = manager->FindOrBuildMaterial("G4_Ar");
   		G4Material* CarbonDioxide = manager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
   		G4Material* Empty  = manager->FindOrBuildMaterial("G4_Galactic");
   		G4Material* Air  = manager->FindOrBuildMaterial("G4_AIR");
   		G4Material* Xenon  = manager->FindOrBuildMaterial("G4_Xe");
   		G4Material* Krypton  = manager->FindOrBuildMaterial("G4_Kr");
  		G4Material* Neon  = manager->FindOrBuildMaterial("G4_Ne");

		//variables for Gas Material
		G4int n_elements(0) ;
   		G4double density(0.), temperature(0.), pressure(0.) ;
   		G4String name, symbol ;
    	
		// CF4 must be defined by handhow to fix trapeziod in 
   		G4Material* CF4 = new G4Material(name="CF4", density=0.003884*g/cm3, n_elements = 2, kStateGas, temperature = 273.15*kelvin, pressure = 1.0*atmosphere);
   			CF4->AddElement(elC, 1) ;
   			CF4->AddElement(elF, 4) ; 

   		//C4F10 defined
   		G4Material* C4F10 = new G4Material(name ="C4F10", density=11.2*mg/cm3, n_elements = 2, kStateGas, temperature = 273.15*kelvin, pressure = 1.0*atmosphere);
   			C4F10->AddElement(elC, 4);
   			C4F10->AddElement(elF, 10);

		//Ar:CO2 (70:30) @ STP conditions
   		G4double mixtureDensity = (Argon->GetDensity() * 70/100.0 + CarbonDioxide->GetDensity() * 30/100.0) ;
   		G4Material* ArCO2 = new G4Material("Ar/CO2", mixtureDensity, 2, kStateGas, temperature = 273.15*kelvin, pressure = 5.*atmosphere);
   			ArCO2->AddMaterial(Argon, 0.7) ;
   			ArCO2->AddMaterial(CarbonDioxide, 0.3) ;

 		//Xe:CO2:C4F10 (45:15:40) @ 10 atmosphere
   		G4Material* XeCO2C4F10 = new G4Material("Xe/CO2/C4F10",density = 96.502*mg/cm3,3, kStateGas, temperature = 273.15*kelvin, pressure = 10.*atmosphere) ;
   			XeCO2C4F10->AddMaterial(Xenon, 0.20) ;
   			XeCO2C4F10->AddMaterial(CarbonDioxide,0.05) ;
   			XeCO2C4F10->AddMaterial(C4F10,0.75) ;

		//Ar:CO2:CF4 (45:15:40) @ STP conditions
  		G4double mixtureDensity1 = (Argon->GetDensity() * 45/100.0 + CarbonDioxide->GetDensity() * 15/100.0 + CF4->GetDensity() * 40/100.0) ;
   		G4Material* ArCO2CF4 = new G4Material("Ar/CO2/CF4",mixtureDensity1,3) ;
   			ArCO2CF4->AddMaterial(Argon, 0.45) ;
   			ArCO2CF4->AddMaterial(CarbonDioxide,0.15) ;
   			ArCO2CF4->AddMaterial(CF4,0.40) ;

		//Xe:Ne:Ar (40:20:40) @10 atmosphere
    		G4Material* XeNeAr = new G4Material("Xe/Ne/Ar", 31.972*mg/cm3,3, kStateGas, temperature = 273.15*kelvin, pressure = 10.*atmosphere) ;
   			XeNeAr->AddMaterial(Argon, 0.4) ;
   			XeNeAr->AddMaterial(Neon, 0.2) ;
   			XeNeAr->AddMaterial(Xenon, 0.4); 

		//define Scintllation Material
   		G4Material* Vinyltoulene = manager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
		G4Material* Cadmiumtungstate = manager->FindOrBuildMaterial("G4_CADMIUM_TUNGSTATE");
	

			EmptyMat =  new MaterialExtension("air", Air); 
    			SciMat =  new MaterialExtension("Scintillation Material", Cadmiumtungstate ); 
   			G10Mat = new MaterialExtension("G10Material", G10Material);
    			InsulationMat = new MaterialExtension("Insolution Material", Kapton);
    			FoilMat =  new MaterialExtension("Foil Material", Copper); 
			GasMat =  new MaterialExtension("Gas Material", XeCO2C4F10 );

	
     	 	//specify the chosen material for different parts
			//fEmptyMat = Air;                                              					//Material for Unfilled Space
  			//fSciMat = Cadmiumtungstate;										//Material for Calorimeter
			//fG10Mat = G10Material; 	 							       		//Material for PCB Boards
			//fInsulationMat = Kapton;
			//fFoilMat = Copper;
			//fGasMat = XeCO2C4F10;
			//fEmptyMat = Air;                                              					//Material for Unfilled Space
  			//fSciMat = SciMat;											//Material for Calorimeter
	
			//fInsulationMat = InsulationMat;
			//fFoilMat = FoilMat;
			//fGasMat = GasMat;
	}

G4VPhysicalVolume* DetectorConstruction::Construct()
	{	
		G4GeometryManager::GetInstance()->OpenGeometry();
		DefineMaterials() ;
	
		//attributes
		G4VisAttributes *cathodeAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.0)) ;
   			cathodeAttributes->SetForceWireframe(true) ;
   		G4VisAttributes *g10Attributes = new G4VisAttributes(G4Colour(0.66,0.8,0.3)) ;
   			g10Attributes->SetForceSolid(true) ;
   		G4VisAttributes *gasAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9)) ;
   			gasAttributes->SetForceSolid(true) ;
   		G4VisAttributes *gemAttributes = new G4VisAttributes(G4Colour(0.0,1.0,0.0)) ;
   			gemAttributes->SetForceSolid(true) ;
		G4VisAttributes *calorimeterAttributes = new G4VisAttributes(G4Colour(0.8888,0.8888,0.0)) ;
   			calorimeterAttributes->SetForceWireframe(true) ;
		G4VisAttributes *emptyAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0)) ;
   			emptyAttributes->SetForceWireframe(true) ;
		G4VisAttributes * crystalAttributes = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  			crystalAttributes->SetForceWireframe(true);
		G4VisAttributes *kaptonAttributes = new G4VisAttributes(G4Colour(1.0, 0.8, 0.0));
  			kaptonAttributes->SetForceWireframe(true);
  		G4VisAttributes *copperAttributes = new G4VisAttributes(G4Colour(0.93,0.60,0.29));
  			copperAttributes->SetForceSolid(true);
		G4VisAttributes *gapAttributes = new G4VisAttributes(G4Colour(0.1,0.2,0.1));
  			gapAttributes->SetForceSolid(true);
		G4VisAttributes *detectorAttributes = new G4VisAttributes ;
   			detectorAttributes->SetVisibility(false) ;
		G4VisAttributes *ringAttributes = new G4VisAttributes ;
   			ringAttributes->SetVisibility(false) ;
	
   		//worldLog->SetVisAttributes(worldAttributes) ;
		G4SDManager* sdman = G4SDManager::GetSDMpointer() ;
		
		ChamberSD* chamberSD = new ChamberSD("Chamber");
		sdman->AddNewDetector(chamberSD);
		
		CalorimeterSD* calorimeterSD = new CalorimeterSD ("Calorimeter");
		sdman->AddNewDetector(calorimeterSD);

		//world volume define / logical volume / placement
		G4double world_hx = 100.*cm;
		G4double world_hy = 100.*cm;
		G4double world_hz = 100.*cm;
	
		G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);
		G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, EmptyMat, "WorldLogical");
			worldLog->SetVisAttributes(new G4VisAttributes(*ringAttributes));
		G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,
					G4ThreeVector(),
					"WorldPhysical",
					worldLog,
					0,
					false,
					0);

		//data essential -- chamber
		G4double chamberBox_hx = 100.*mm ;	
		G4double chamberBox_hy = chamberBox_hx ;
        	G4double chamberBox_hz = 89.58002*mm;

		//data essential -- trapezoidal box in which chamber & calorimeter will bw arranged
		G4int n_detector = 18 ;
		G4double angPhi = twopi/n_detector; 
		G4double half_angPhi = 0.5*angPhi;
  		G4double cosPhi = std::cos(half_angPhi);
  		G4double tanPhi = std::tan(half_angPhi);

		//data essential -- detector box
		G4double calorimeter_hz = 25.*mm;
		G4double detector_hz = 0.5*(chamberBox_hz+(2.*calorimeter_hz));

		//data essential -- calorimeter
		G4double calorimeter_hx = 0.5*chamberBox_hx + detector_hz*tanPhi ;                                          //by geometry
        	G4double calorimeter_hy = 0.5*chamberBox_hy + detector_hz*tanPhi ; 
		

		
		G4double detectorLarge_hx = 0.5*chamberBox_hx + 2*detector_hz*tanPhi ;
		G4double detectorLarge_hy = 0.5*chamberBox_hy + 2*detector_hz*tanPhi ;
		G4double detectorShort_hx = 0.5*chamberBox_hx;
		G4double detectorShort_hy = 0.5*chamberBox_hy;

		//data essential -- ring in which trapezoidal detectors will be placed
  		G4double ring_R1 = (0.5*chamberBox_hy)/tanPhi;
	  	G4double ring_R2 = (ring_R1+2.*detector_hz)/cosPhi;	
		G4double ring_hz = detectorLarge_hx ;

           	//height= 2*total_thick;
           	//G4cout<<"height = "<<height<<G4endl;
               
		//defining ring 
		G4Tubs* detectorRing = new G4Tubs("DetectorRing", ring_R1, ring_R2, ring_hz, 0.,twopi);	
		G4LogicalVolume* detectorRingLog = new G4LogicalVolume(detectorRing, GasMat, "DetectorRingLogical");
			detectorRingLog->SetVisAttributes(new G4VisAttributes(*ringAttributes)) ;
		
		//ring placements
		G4VPhysicalVolume* detectorRingPhys = new G4PVPlacement(0,                     				//no rotation//to match edge of ring and trapezium
                      						  G4ThreeVector(0, 0, 0), 				//position
                      						  detectorRingLog,             				//its logical volume
                      						  "RingPyhsical",                			//its name
                      						  worldLog,         					//its mother  volume
                      						  false,                 				//no boolean operation
								  0,							//copy
         							  fCheckOverlaps);							

		//defining trapezoidal detector
		G4Trd* detectorBox = new G4Trd("Detector", detectorLarge_hx, detectorShort_hx, detectorLarge_hy, detectorShort_hy, detector_hz);
		G4LogicalVolume* detectorBoxLog = new G4LogicalVolume(detectorBox, EmptyMat, "DetectorLogical");
			detectorBoxLog->SetVisAttributes(new G4VisAttributes(*detectorAttributes)) ;
	
		//placement of detectors in ring
			for (G4int idetector = 0; idetector < n_detector ; ++idetector) 
				{
    					G4double phi = idetector*angPhi;
    					G4RotationMatrix rotm  = G4RotationMatrix();
    					rotm.rotateY(270*deg); 
    					rotm.rotateZ(phi);
    					G4ThreeVector posZ = G4ThreeVector(std::cos(phi),  std::sin(phi),0.);     
    					G4ThreeVector position = (ring_R1+detector_hz)*posZ;
					G4Transform3D transform = G4Transform3D(rotm,position);
                                
					//placement of ith detector in the ring    
    					new G4PVPlacement(transform,							//rotation,position
                      					  detectorBoxLog,            					//its logical volume
                      					  "Detector",             					//its name
                      					  detectorRingLog,             					//its mother  volume
                      					  false,                 					//no boolean operation
                      					  idetector,                 					//copy number
                      					  fCheckOverlaps);       					//checking overlap
				}//for loop ends here 

 		//rotating the arrangement to align with the axes of ring
		G4RotationMatrix* rotationPlacement = new G4RotationMatrix() ;
   		//rotationPlacement->rotateY(M_PI / 2.0) ;
   		//rotationPlacement->rotateX(M_PI / 2.0) ;
   		rotationPlacement->rotateY(twopi/2) ;
   		rotationPlacement->rotateX(0) ;
		//rotationPlacement->rotateZ(180*deg) ;	
      	
		//defineing Chamber with triple GEM
		
		// fake A												//chamberbox collection start here
		G4Box* fakeA = ChamberBox("FakeA", chamberBox_hx, chamberBox_hy, 1.*nm);
		G4LogicalVolume* fakeALog = new G4LogicalVolume(fakeA, EmptyMat, "FakeALog");
		chamberBoxCollection.push_back(fakeA);
   		chamberBoxLogCollection.push_back(fakeALog); 
		//fakeALog->SetSensitiveDetector(sensitive);

   		//drift cathode foil
  		G4Box* kapton0 = ChamberBox("Kapton0", chamberBox_hx, chamberBox_hy, 200.*um) ;
   		G4LogicalVolume* kapton0Log = new G4LogicalVolume(kapton0, InsulationMat, "Kapton0Log") ;
		chamberBoxCollection.push_back(kapton0);
   		chamberBoxLogCollection.push_back(kapton0Log);    	
			kapton0Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
		
		//first PCB drift board
  		G4Box* g10_1 = ChamberBox("G10_1", chamberBox_hx, chamberBox_hy, 3.*mm) ;
  		G4LogicalVolume* g10_1Log = new G4LogicalVolume(g10_1, G10Mat, "G10_1Log") ;
   		chamberBoxCollection.push_back(g10_1);
   		chamberBoxLogCollection.push_back(g10_1Log); 
			g10_1Log->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
		
		//first gas material / drift gap
   		G4Box* gasGap1D = ChamberBox("GasGap1D", chamberBox_hx, chamberBox_hy, 50.*mm) ;
   		G4LogicalVolume* gasGap1DLog = new G4LogicalVolume(gasGap1D, GasMat, "GasGap1DLog") ; 
		chamberBoxCollection.push_back(gasGap1D);
   		chamberBoxLogCollection.push_back(gasGap1DLog); 
			gasGap1DLog->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;	
			gasGap1DLog->SetSensitiveDetector(chamberSD);

		//first foil GEM 1 begins/ defining copper layer of GEM 1 top
   		G4Box* copper1T = ChamberBox("Copper1T", chamberBox_hx, chamberBox_hy, 5*um) ;
   		G4LogicalVolume* copper1TLog = new G4LogicalVolume(copper1T, FoilMat, "Copper1TLog") ; 
   		chamberBoxCollection.push_back(copper1T) ;
   		chamberBoxLogCollection.push_back(copper1TLog) ;
			copper1TLog->SetVisAttributes(new G4VisAttributes(*copperAttributes)) ;
	
		//kapton layer of GEM 1
   		G4Box* kapton1 = ChamberBox("Kapton1", chamberBox_hx, chamberBox_hy, 50.*um) ;
   		G4LogicalVolume* kapton1Log = new G4LogicalVolume(kapton1, InsulationMat, "Kapton1Log") ;
   		chamberBoxCollection.push_back(kapton1) ;
   		chamberBoxLogCollection.push_back(kapton1Log) ;
			kapton1Log->SetVisAttributes(new G4VisAttributes(*kaptonAttributes)) ;
	
		//copper layer of GEM 1 bottom
   		G4Box* copper1B = ChamberBox("Copper1B", chamberBox_hx, chamberBox_hy, 5.*um) ;
   		G4LogicalVolume* copper1BLog = new G4LogicalVolume(copper1B, FoilMat, "copper1BLog") ;
   		chamberBoxCollection.push_back(copper1B) ;
   		chamberBoxLogCollection.push_back(copper1BLog) ; 
			copper1BLog->SetVisAttributes(new G4VisAttributes(*copperAttributes)) ;
   		//first foil GEM 1 ends

		//second gas material / transfer 1 gap
   		G4Box* gasGap2T1 = ChamberBox("GasGap2T1", chamberBox_hx, chamberBox_hy, 4.*mm) ;
   		G4LogicalVolume* gasGap2T1Log = new G4LogicalVolume(gasGap2T1, GasMat, "GasGap2T1Log") ; 
   		chamberBoxCollection.push_back(gasGap2T1);
   		chamberBoxLogCollection.push_back(gasGap2T1Log);
			gasGap2T1Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;    	
			gasGap2T1Log->SetSensitiveDetector(chamberSD);

		//second foil GEM 2 begins/ defining copper layer of GEM 2 top
   		G4Box* copper2T = ChamberBox("Copper2T", chamberBox_hx, chamberBox_hy, 5*um) ;
   		G4LogicalVolume* copper2TLog = new G4LogicalVolume(copper2T, FoilMat, "Copper2TLog") ; 
   		chamberBoxCollection.push_back(copper2T) ;
   		chamberBoxLogCollection.push_back(copper2TLog) ;
			copper2TLog->SetVisAttributes(new G4VisAttributes(*copperAttributes)) ;
		//kapton layer of GEM 2
   		G4Box* kapton2 = ChamberBox("Kapton2", chamberBox_hx, chamberBox_hy, 50.*um) ;
   		G4LogicalVolume* kapton2Log = new G4LogicalVolume(kapton2, InsulationMat, "Kapton2Log") ;   	
   		chamberBoxCollection.push_back(kapton2) ;
   		chamberBoxLogCollection.push_back(kapton2Log) ;
			kapton2Log->SetVisAttributes(new G4VisAttributes(*kaptonAttributes)) ;

		//copper layer of GEM 2 bottom
   		G4Box* copper2B = ChamberBox("Copper2B", chamberBox_hx, chamberBox_hy, 5.*um) ;
   		G4LogicalVolume* copper2BLog = new G4LogicalVolume(copper2B, FoilMat, "copper2BLog") ;
   		chamberBoxCollection.push_back(copper2B) ;
   		chamberBoxLogCollection.push_back(copper2BLog) ;
			copper2BLog->SetVisAttributes(new G4VisAttributes(*copperAttributes)) ; 
   		//second foil GEM 2 ends

		//third gas material / transfer 2 gap
   		G4Box* gasGap3T2 = ChamberBox("GasGap3T2", chamberBox_hx, chamberBox_hy, 4.*mm) ;
   		G4LogicalVolume* gasGap3T2Log = new G4LogicalVolume(gasGap3T2, GasMat, "GasGap3T2Log") ;    		
		chamberBoxCollection.push_back(gasGap3T2);
   		chamberBoxLogCollection.push_back(gasGap3T2Log);
			gasGap3T2Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
			gasGap3T2Log->SetSensitiveDetector(chamberSD);
			    	
	
		//third foil / GEM 3 begins/ defining copper layer of GEM 3 top
   		G4Box* copper3T = ChamberBox("Copper3T", chamberBox_hx, chamberBox_hy, 5*um) ;
   		G4LogicalVolume* copper3TLog = new G4LogicalVolume(copper3T, FoilMat, "Copper3TLog") ; 
   		chamberBoxCollection.push_back(copper3T) ;
   		chamberBoxLogCollection.push_back(copper3TLog) ;
			copper3TLog->SetVisAttributes(new G4VisAttributes(*copperAttributes)) ;
		
		//kapton layer of GEM 3
   		G4Box* kapton3 = ChamberBox("Kapton3", chamberBox_hx, chamberBox_hy, 50.*um) ;
   		G4LogicalVolume* kapton3Log = new G4LogicalVolume(kapton3, InsulationMat, "Kapton3Log") ;
   		chamberBoxCollection.push_back(kapton3) ;
   		chamberBoxLogCollection.push_back(kapton3Log) ;
			kapton3Log->SetVisAttributes(new G4VisAttributes(*kaptonAttributes)) ;
		
		//copper layer of GEM 3 bottom
   		G4Box* copper3B = ChamberBox("Copper3B", chamberBox_hx, chamberBox_hy, 5.*um) ;
   		G4LogicalVolume* copper3BLog = new G4LogicalVolume(copper3B, FoilMat, "copper3BLog") ;   		
   		chamberBoxCollection.push_back(copper3B) ;
   		chamberBoxLogCollection.push_back(copper3BLog) ;
			copper3BLog->SetVisAttributes(new G4VisAttributes(*copperAttributes)) ; 
   	   	//third foil GEM 3 ends

		//fourth gap / induction gap
		G4Box* gasGap4I = ChamberBox("GasGap4I", chamberBox_hx, chamberBox_hy, 5.*mm) ;
   		G4LogicalVolume* gasGap4ILog = new G4LogicalVolume(gasGap4I, GasMat, "GasGap4ILog") ;   		
   		chamberBoxCollection.push_back(gasGap4I) ;
   		chamberBoxLogCollection.push_back(gasGap4ILog) ;
			gasGap4ILog->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
			gasGap4ILog->SetSensitiveDetector(chamberSD);

		//readout board anode
 		G4Box* g10_2 = ChamberBox("G10_2", chamberBox_hx, chamberBox_hy, 3.*mm) ;
   		G4LogicalVolume* g10_2Log = new G4LogicalVolume(g10_2, G10Mat, "G10_2Log") ;
   		chamberBoxCollection.push_back(g10_2) ;
   		chamberBoxLogCollection.push_back(g10_2Log) ;
 			g10_2Log->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
	
		//readout anode foil
   		G4Box* kapton4 = ChamberBox("kapton4", chamberBox_hx, chamberBox_hy, 200.*um) ;
   		G4LogicalVolume* kapton4Log = new G4LogicalVolume(kapton4, InsulationMat, "Kapton4Log") ;
   		chamberBoxCollection.push_back(kapton4) ;
   		chamberBoxLogCollection.push_back(kapton4Log) ;
   			kapton4Log->SetVisAttributes(new G4VisAttributes(*kaptonAttributes)) ;
 		
		//fake B
 		G4Box* fakeB = ChamberBox("FakeB", chamberBox_hx, chamberBox_hy, 1.*nm) ;
   		G4LogicalVolume* fakeBLog = new G4LogicalVolume(fakeB, EmptyMat, "FakeBLog") ;
   		chamberBoxCollection.push_back(fakeB) ;
   		chamberBoxLogCollection.push_back(fakeBLog) ;
   		//fakeBLog->SetSensitiveDetector(sensitive) ;

		//gap for chamber & calorimeter
		G4Box* gapCC = ChamberBox("GapCC", chamberBox_hx, chamberBox_hy, 20.*mm) ;
   		G4LogicalVolume* gapCCLog = new G4LogicalVolume(gapCC, EmptyMat, "GapCC") ;	   	
		chamberBoxCollection.push_back(gapCC) ;
   		chamberBoxLogCollection.push_back(gapCCLog) ;
			gapCCLog->SetVisAttributes(new G4VisAttributes(*emptyAttributes)) ;	      			//chamberbox collection ends here
		
		
	
		//calorimeter
		/*G4Box* calorimeterBox = ChamberBox("CalorimeterSolid", calorimeter_hx, calorimeter_hy, calorimeter_hz);
  		G4LogicalVolume* calorimeterLog = new G4LogicalVolume(calorimeterBox, fEmptyMat, "CalorimeterLogical"); 
   		chamberBoxCollection.push_back(calorimeterBox) ;
   		chamberBoxLogCollection.push_back(calorimeterLog) ;
			calorimeterLog->SetVisAttributes(new G4VisAttributes(*calorimeterAttributes)) ;
			calorimeterLog->SetSensitiveDetector(sensitive);*/

		//defining calorimeter 
		G4Box* calorimeterBox = new G4Box("CalorimeterSolid", calorimeter_hx, calorimeter_hy, calorimeter_hz);
  		G4LogicalVolume* calorimeterLog = new G4LogicalVolume(calorimeterBox, EmptyMat, "CalorimeterLogical");
			calorimeterLog->SetVisAttributes(new G4VisAttributes(*calorimeterAttributes)) ;  	
		
		//placement of calorimeter 
		G4VPhysicalVolume* calorimeterPhys = new G4PVPlacement(0,
								G4ThreeVector(0, 0, -0.5*detector_hz),
								calorimeterLog,
								"CalorimeterPhysical",
								detectorBoxLog,
								false,
								0);

		//data essential -- crystal of calorimeter
		G4double crystal_hx = calorimeter_hx/10;
  		G4double crystal_hy = calorimeter_hy/10;
  		G4double crystal_hz = 2.5*cm;
  		
		//defining crystal
		G4Box* crystalSolid = new G4Box("CrystalSolid", crystal_hx, crystal_hy, crystal_hz);
  		G4LogicalVolume* crystalLog = new G4LogicalVolume(crystalSolid, SciMat, "CrystalLogical");
			crystalLog->SetVisAttributes(*crystalAttributes);		
			crystalLog->SetSensitiveDetector(calorimeterSD);
	
		//placements inside the calorimeter
		G4String tName1("Crystal");        //Allow all target physicals to share same name (delayed copy)
  		G4int copyNo=0;
  		G4double yTlate, xTlate;
  		nX = 10;
  		nY = 10;
		//placement of crystals in calorimeter 
  			for (G4int j = 0; j < nY; ++j)
    				{
      					yTlate = -calorimeter_hy + 1*crystal_hy + j*2*crystal_hy;
      			for (G4int i = 0; i < nX; ++i)
        			{
   					xTlate = -calorimeter_hx + 1*crystal_hx + i*2*crystal_hx;
     	
					//placement of each copy of crystal
					new G4PVPlacement(0,
					G4ThreeVector(xTlate, yTlate, 0.*cm),
                  			tName1,
                    			crystalLog,
                   			calorimeterPhys,
					false,
					copyNo++,
					false);
        			}//for loop i ends
				}//for loop j ends
	
		//Placement of chamber collection in trapezoidal detector
		PlaceGeometry(rotationPlacement,G4ThreeVector(0, 0, 69.790001*mm),detectorBoxLog);
		
		//always return the world physical volume
		return worldPhys ; 

	 	//print the dimensions of all the detector units
                G4cout<<"chamberBox_hx = "<<chamberBox_hx<<G4endl;
                G4cout<<"chamberBox_hy = "<<chamberBox_hy<<G4endl;
                G4cout<<"chamberBox_hx = "<<chamberBox_hz<<G4endl;
                G4cout<<"calorimeter_hx= "<<calorimeter_hx<<G4endl;
                G4cout<<"calorimeter_hy= "<<calorimeter_hy<<G4endl;
                G4cout<<"calorimeter_hz= "<<calorimeter_hz<<G4endl;
                G4cout<<"detectorLarge_hx= "<<detectorLarge_hx<<G4endl;
                G4cout<<"detectorLarge_hy= "<<detectorLarge_hy<<G4endl;
                G4cout<<"detectorShort_hx= "<<detectorShort_hx<<G4endl;
                G4cout<<"detectorShort_hy= "<<detectorShort_hy<<G4endl;
                G4cout<<"detector_hz = "<<detector_hz<<G4endl;
		G4cout<<"Inner radius= "<<ring_R1<<G4endl;
		G4cout<<"Outer radius= "<<ring_R2<<G4endl;
		G4cout<<"width of ring= "<<ring_hz<<G4endl;
		G4cout<<"crystal_hx= "<<crystal_hx<<G4endl;
		G4cout<<"crystal_hy= "<<crystal_hy<<G4endl;
 		G4cout<<"crystal_hz= "<<crystal_hz<<G4endl;			
	}

G4Box* DetectorConstruction::ChamberBox(G4String name, G4double length, G4double breadth, G4double width) 
	{
		//shape of chamber		
		G4Box* shape = new G4Box(name,
	 				length/2,
	 				breadth/2,
	 				width/2) ;
   		return shape ;
	}

void DetectorConstruction::PlaceGeometry(G4RotationMatrix *pRot, G4ThreeVector tlate, G4LogicalVolume* pMotherLogical)
	{
		//translating layer of GEM 		
		G4double ZTranslation = 0 ;

			for(size_t i=0 ; i<chamberBoxCollection.size() ; i++)
				{
					ZTranslation += chamberBoxCollection.at(i)->GetZHalfLength() ;
      					G4ThreeVector position = tlate + G4ThreeVector(0, 0, ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
				
					//placement of ith layers of chamber
      					new G4PVPlacement(pRot,
	    						position,
	    						chamberBoxLogCollection.at(i),
	    						chamberBoxCollection.at(i)->GetName(),
	    						pMotherLogical,
	    						false,
	    						i) ;
					ZTranslation += chamberBoxCollection.at(i)->GetZHalfLength() ;	
				}
	}

void DetectorConstruction::ConstructSDandField()
	{}










