// Ed Callaghan
// Base class for one-at-a-time muon beams
// April 2024

#include <MuonBeam.h>

MuonBeam::MuonBeam(){
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* def = particleTable->FindParticle("mu-");

    // this->gun = new G4ParticleGun(1);
    this->gun = new ParticleGun(1);
    this->gun->SetParticleDefinition(def);
}

MuonBeam::~MuonBeam(){
    delete this->gun;
}

void MuonBeam::GeneratePrimaries(G4Event* event){
    this->SampleMuonState();
    this->gun->SetParticlePosition(this->position);
    this->gun->SetParticleMomentum(this->momentum, 0);
    this->gun->GeneratePrimaryVertex(event);
}
