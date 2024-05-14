// Teja Nivarthi
// Edited version of G4ParticleGun class to include verbosity when changing momentum
// May 2024

#include <ParticleGun.h>

ParticleGun::ParticleGun(G4int numberofparticles) : G4ParticleGun(numberofparticles) {}

ParticleGun::~ParticleGun() {}

void ParticleGun::SetParticleMomentum(G4double aMomentum, bool verbose) {
  //  if((particle_energy>0.0) && (verbose)){
  //    if(particle_definition){
  //      G4cout << "G4ParticleGun::" << particle_definition->GetParticleName()
  //             << G4endl;
  //    }else{
  //      G4cout << "G4ParticleGun::" << " " << G4endl;
  //    }
  //    G4cout << " was defined in terms of KineticEnergy: "
  //           << particle_energy/CLHEP::GeV << "GeV"   << G4endl;
  //    G4cout << " is now defined in terms Momentum: "
  //           << aMomentum/CLHEP::GeV       << "GeV/c" << G4endl;
  //  }
   if(particle_definition==0)
   {
     G4cout <<"Particle Definition not defined yet for G4ParticleGun"<< G4endl;
     G4cout <<"Zero Mass is assumed"<<G4endl;
     particle_momentum = aMomentum;
     particle_energy = aMomentum;
   }
   else
   {
     G4double mass =  particle_definition->GetPDGMass();
     particle_momentum = aMomentum;
     particle_energy = std::sqrt(particle_momentum*particle_momentum+mass*mass)-mass;
   }
}

void ParticleGun::SetParticleMomentum(G4ParticleMomentum aMomentum, bool verbose) {
  // if((particle_energy>0.0)){
  //   if(particle_definition){
  //     G4cout << "G4ParticleGun::" << particle_definition->GetParticleName()
  //            << G4endl;
  //   }else{
  //    G4cout << "G4ParticleGun::" << " " << G4endl;
  //   }
  //   G4cout << " was defined in terms of KineticEnergy: "
  //          << particle_energy/CLHEP::GeV << "GeV"   << G4endl;
  //   G4cout << " is now defined in terms Momentum: "
  //          << aMomentum.mag()/CLHEP::GeV << "GeV/c" << G4endl;
  // }
  if(particle_definition==0)
  {
    G4cout <<"Particle Definition not defined yet for G4ParticleGun"<< G4endl;
    G4cout <<"Zero Mass is assumed"<<G4endl;
    particle_momentum_direction =  aMomentum.unit();
    particle_momentum = aMomentum.mag();
    particle_energy = aMomentum.mag();
  } 
  else 
  {
    G4double mass =  particle_definition->GetPDGMass();
    particle_momentum = aMomentum.mag();
    particle_momentum_direction =  aMomentum.unit();
    particle_energy = std::sqrt(particle_momentum*particle_momentum+mass*mass)-mass;
  }
}