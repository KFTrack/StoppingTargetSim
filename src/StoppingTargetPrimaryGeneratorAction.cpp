// Ed Callaghan
// User-level primary generator action
// October 2023

#include <StoppingTargetPrimaryGeneratorAction.h>

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
    this->gun->GeneratePrimaryVertex(event);
}
