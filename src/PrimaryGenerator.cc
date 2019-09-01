//generating primary events

//user defined header file include
#include "PrimaryGenerator.hh"

//geant4 includes
#include "G4SystemOfUnits.hh"
#include "G4HadPhaseSpaceGenbod.hh"
#include "globals.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh" 
#include "G4TransportationManager.hh" 
#include "G4Navigator.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"
#include "G4Circle.hh"
#include "G4LorentzVector.hh"

PrimaryGenerator::PrimaryGenerator()
		:G4VPrimaryGenerator()
	{
  		G4cout<<"Sodium Generator is called"<<G4endl;
	}

PrimaryGenerator::~PrimaryGenerator() 
	{}

/*void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
	{    
		G4cout<<"In GeneratorPrimaryVertex"<<G4endl;
    	//create vertex of 2g/ 3g and if needed add de-excitation gamma quanta to this vertex
    	G4double time = 0*s;
	
	    //G4ThreeVector* boost = new G4ThreeVector(0,0,0);
     	//HepBoost* boost = new HepBoost(Hep3Vector direction(1,0,0),0.1);

    	//G4ThreeVector vtxPosition;
    	//int a;
    	//std::tie(vtxPosition, a) = GetVerticesDistribution();

    	G4PrimaryVertex* vertex = new G4PrimaryVertex(VertexUniformInCylinder(1*cm,1*cm), time);
    	//G4PrimaryVertex* vertex = new G4PrimaryVertex(VertexUniformInCylinder(1*mm,1*mm), time);
  		//const G4ThreeVector bo(0.1,0,0);

		//GeneratePromptGammaSodium(vertex);
		//GenerateTwoGammaVertex(vertex);
		//GeneratePromptGammaSodium(vertex);
		//GenerateThreeGammaVertex(vertex);
		event->AddPrimaryVertex(vertex);  
	}
*/
G4ThreeVector PrimaryGenerator::VertexUniformInCylinder(G4double rSquare, G4double zmax)
	{
  		//vertex A uniform on a cylinder 
  		//const G4double rSquare = 144*cm;
  		//const G4double zmax = 34*cm;
  
		CLHEP::HepRandom::setTheEngine(new CLHEP::DRand48Engine);
        G4int Seed =time(NULL)*G4UniformRand();
        G4cout<<"seed for the event="<<Seed<<G4endl;
        long seeds[2];
        seeds[0]=(long) Seed; 
        seeds[1]=(long) (Seed * G4UniformRand());
        CLHEP::HepRandom::getTheEngine()->setSeeds(seeds, -1);
    	/*G4double cosTheta = -1.0+2.0*G4UniformRand();
        G4double phi = twopi * G4UniformRand();
        G4double sinTheta = sqrt(1-cosTheta*cosTheta);
		particleGun->SetParticleMomentumDirection(G4ThreeVector(sinTheta * cos(phi) , sinTheta * sin(phi), cosTheta));

      	G4double alpha = twopi*G4UniformRand();     //alpha uniform in (0, 2*pi)
  		G4double ux = std::cos(alpha);
  		G4double uy = std::sin(alpha);
  		G4double z = zmax*(2*G4UniformRand() - 1);  //z uniform in (-zmax, +zmax)
  		G4ThreeVector positionA(r*ux,r*uy,z);*/

		G4double r = std::sqrt(rSquare*G4UniformRand());
		G4double alpha = 0.5*twopi  /* (3.14/180)*twopi*G4UniformRand()*/;     //alpha uniform in (0, 2*pi)
   		G4cout<<"alpha for the event="<<alpha<<G4endl;
  		G4double ux = std::cos(alpha);
  		G4double uy = std::sin(alpha);
  		G4double z = zmax*(2*G4UniformRand() - 1);  //z uniform in (-zmax, +zmax)
  		G4ThreeVector positionA(r*ux,r*uy,z);
  
  		return positionA;
	}

std::tuple<G4ThreeVector,int> PrimaryGenerator::GetVerticesDistribution()
	{
    	G4bool lookForVtx = false;
    	G4ThreeVector myPoint(0,0,0);

    	//annihilation will occure only in materials where it was allowed @see MaterialExtension
    	//annihilation rate 2g/3g also depends on the material type
    	//now assumed equal distribution in the target - this may be modified in the future
    	while (!lookForVtx)
    		{
        		G4double x_tmp = 10.*(2*G4UniformRand() - 1)*cm;
        		G4double y_tmp = 10.*(2*G4UniformRand() - 1)*cm;
        		G4double z_tmp = 10.*(2*G4UniformRand() - 1)*cm;

        		myPoint.setX(x_tmp);
        		myPoint.setY(y_tmp);
        		myPoint.setZ(z_tmp);

        		G4Navigator* theNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
        		MaterialExtension* mat = (MaterialExtension*)theNavigator->LocateGlobalPointAndSetup(myPoint)->GetLogicalVolume()->GetMaterial()  ; 
        		lookForVtx = mat->IsTarget();
			};
 
    	return std::make_tuple(myPoint,4);
	}

void PrimaryGenerator::GenerateTwoGammaVertex(G4PrimaryVertex* vertex )
	{
     	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
     	G4ParticleDefinition* particleDefinition = particleTable->FindParticle("gamma");

		const G4double en = 511*keV;
		double theta = (90+10*(1 - 2 * G4UniformRand()))*deg;//(72.24*(1-2 * G4UniformRand()))*deg;
		double phi = 2 * M_PI * G4UniformRand();
     	//double phi = acos(1 - 2 * G4UniformRand());
     	double px = en * sin(theta) * cos(phi);
     	double py = en * sin(theta) * sin(phi);
     	double pz = en * cos(theta);
		double psqr = px*px + py*py +pz*pz;

		for (int i=0; i<2; i++)
     		{
				if(i==0)
					{
						G4PrimaryParticle* particle1 = new G4PrimaryParticle(particleDefinition, px,py,pz,en);
							particle1->SetPolarization(0,1,0);
							//particle1->SetUserInformation(gamma1);
        					
        				vertex->SetPrimary(particle1);
        			}
		
				if(i==1)
					{
						G4PrimaryParticle* particle1 = new G4PrimaryParticle(particleDefinition, -px,-py,-pz,en);
							particle1->SetPolarization(0,0,1);
							//particle1->SetUserInformation(gamma2);
				
						vertex->SetPrimary(particle1);
					}
			}



     		/*mass = 1022*keV;
     		mass_secondaries = {0., 0.};
     		std::vector<G4LorentzVector> out;
    		std::vector<G4ThreeVector> out;
     		G4HadPhaseSpaceGenbod* phS = new G4HadPhaseSpaceGenbod();
     		phS->Generate(mass,mass_secondaries,out);
		if(abs (out[0].pz())<=0.0500){
		G4cout<<phS->AcceptEvent()<<G4endl;//}
		G4cout<<"out----------------"<<out<<G4endl;

		//CLHEP::HepLorentzVector::cosTheta(out.Pz())
		//if(abs (CLHEP::HepLorentzVector::pz().out)<=0.0500){
		//if (abs(out[0].pz())<0.0500) //&& abs(out[1].pz())<0.0500){
		{
     		// boost gamma quanta
     		for (int i=0; i<2; i++)
     			{
				
      				// out[i].boost(/*BoostAxis,*///0.1);
     				// out[i].boost(0.1,0.1,0.0);
        			//if(abs (out[i].pz())<=0.0500){
				//G4PrimaryParticle* particle1 = new G4PrimaryParticle(particleDefinition, out[i].px(),0.05*out[i].py(),0.05*out[i].pz(),out[i].e());
          				//particle1->SetUserInformation(particleID);
        			//fParticleNumber = i;
      				//fHisto->GetChamberBox()->Fill();
           			//fHisto->FillChamberBox();
				//G4cout<<"Primarygene....."<<out[i].px()<<"..."<<out[i].py()<<"..."<<out[i].pz()<<"..."<<out[i].e()<<G4endl;
				
        			//vertex->SetPrimary(particle1);
				//}
			//}*/
	}

/*void PrimaryGenerator::GenerateThreeGammaVertex(G4PrimaryVertex* vertex )
	{
     		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
     		G4ParticleDefinition* particleDefinition = particleTable->FindParticle("gamma");

     		Double_t mass_secondaries[3] = {0., 0., 0.};
     		TGenPhaseSpace event;
     		TLorentzVector vec_pozytonium(0.0,0.0,0.0,1022);
     		Bool_t test =  event.SetDecay(vec_pozytonium, 3, mass_secondaries);
     		
		if( !test)
			{
         			std::cout   << "error: generate_gamma : createThreeEvts:" << test << std::endl;  
     			}

     		Double_t weight;
     		Double_t weight_max= event.GetWtMax()*pow(10,5);
     		Double_t rwt;  
     		Double_t M_max = 7.65928*pow(10,-6);    
      		
		do
			{
          			weight = event.Generate();        
          			weight = weight*calculate_mQED(511,event.GetDecay(0)->E(),event.GetDecay(1)->E(),event.GetDecay(2)->E());
          			rwt = M_max*weight_max*(G4UniformRand());
      			}
		while( rwt > weight );    
		event.Generate();   
     		for (int i=0; i<3; i++)
     			{
        			TLorentzVector * out = event.GetDecay(i);
        			G4PrimaryParticle* particle1 = new G4PrimaryParticle(particleDefinition, out->Px()*keV,out->Py()*keV,out->Pz()*keV,out->E()*keV);  //MeV
				vertex->SetPrimary(particle1);
     			}
	}*/

void PrimaryGenerator::GeneratePromptGammaSodium(G4PrimaryVertex* vertex ) 
	{
     		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
     		G4ParticleDefinition* particleDefinition = particleTable->FindParticle("gamma");

     		const G4double ene = 1.2770*MeV;
		double theta = 2 * M_PI * G4UniformRand();
     		double phi = acos(1 - 2 * G4UniformRand());
     		double px = ene * sin(phi) * cos(theta);
     		double py = ene * sin(phi) * sin(theta);
     		double pz = ene * cos(phi);

     		G4PrimaryParticle* particle1 = new G4PrimaryParticle(particleDefinition, px, py, pz,ene);
		vertex->SetPrimary(particle1);
      		//printf(" %f \n", sqrt(pow(px,2)+pow(py,2)+pow(pz,2)));
	}

/*void PrimaryGenerator::SetUserInformation(G4VUserPrimaryParticleInformation* particleID)
	{}*/
void PrimaryGenerator::GeneratePrimaryVertex(G4Event* event)
	{    
		G4cout<<"In GeneratorPrimaryVertex"<<G4endl;
    		//create vertex of 2g/ 3g and if needed add de-excitation gamma quanta to this vertex
    		G4double time = 0*s;
	
	     	//G4ThreeVector* boost = new G4ThreeVector(0,0,0);
     		//HepBoost* boost = new HepBoost(Hep3Vector direction(1,0,0),0.1);

    		//G4ThreeVector vtxPosition;
    		//int a;
    		//std::tie(vtxPosition, a) = GetVerticesDistribution();

    		G4PrimaryVertex* vertex = new G4PrimaryVertex(VertexUniformInCylinder(1*cm,1*cm), time);
    		//G4PrimaryVertex* vertex = new G4PrimaryVertex(VertexUniformInCylinder(1*mm,1*mm), time);
  		//const G4ThreeVector bo(0.1,0,0);

		//GeneratePromptGammaSodium(vertex);
		//GenerateTwoGammaVertex(vertex);
		//GeneratePromptGammaSodium(vertex);
		//GenerateThreeGammaVertex(vertex);
		//if (abs(out[0].pz())<0.0500){
		GenerateTwoGammaVertex(vertex);
		event->AddPrimaryVertex(vertex);  //}
	}

Double_t PrimaryGenerator::calculate_mQED(Double_t mass_e, Double_t w1, Double_t w2, Double_t w3)
	{ 
   		Double_t mQED = pow((mass_e-w1)/(w2*w3),2) + pow((mass_e-w2)/(w1*w3),2) + pow((mass_e-w3)/(w1*w2),2); 
  		return mQED;
 	}


