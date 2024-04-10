// Ed Callaghan
// User-level primary generator action
// October 2023

#include <StoppingTargetPrimaryGeneratorAction.h>
using namespace std;

StoppingTargetPrimaryGeneratorAction::StoppingTargetPrimaryGeneratorAction(){
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* def = particleTable->FindParticle("mu-");

    this->gun = new G4ParticleGun(1);
    this->gun->SetParticleDefinition(def);

    // double energy = ...;
    // this->gun->SetParticleEnergy(energy);

    // completely made up
    G4ThreeVector position(0.0 * CLHEP::m, 0.0, 0.0 * CLHEP::m);
    this->gun->SetParticlePosition(position);

    // canonical momentum entering detector solenoid
    G4ThreeVector momentum(0.0 * CLHEP::MeV, 0.0, 50.0 * CLHEP::MeV);
    this->gun->SetParticleMomentum(momentum);
}

StoppingTargetPrimaryGeneratorAction::~StoppingTargetPrimaryGeneratorAction(){
    delete this->gun;
}

// TODO eventually, this will update the gun before each shot
void StoppingTargetPrimaryGeneratorAction::GeneratePrimaries(G4Event* event){
    double newX, newY;
    double r, theta;

    double Rmin = 0.0215;
    double Rmax = 0.075;

    double Umin = pow(Rmin, 2) / 2;
    double Umax = pow(Rmax, 2) / 2;

    theta = G4UniformRand() * 2 * CLHEP::pi;
    r = pow(2 * G4UniformRand() * (Umax - Umin) + Umin, 0.5);

    newX = r * cos(theta) * CLHEP::m;
    newY = r * sin(theta) * CLHEP::m;
    // cout << newX << " " << newY << endl;
    G4ThreeVector newPosition(newX, newY, 0.0 * CLHEP::m);
    // randomly generate new position
    this->gun->SetParticlePosition(newPosition);
    this->gun->GeneratePrimaryVertex(event);
}
