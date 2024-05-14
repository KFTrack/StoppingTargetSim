// Teja Nivarthi
// Edited version of G4ParticleGun class to include verbosity when changing momentum
// May 2024

#ifndef PARTICLEGUN_H
#define PARTICLEGUN_H

#include <G4ParticleGun.hh>
#include <G4ios.hh>
#include <CLHEP/Units/PhysicalConstants.h>

class ParticleGun : public G4ParticleGun {
    public:
        ParticleGun(G4int numberofparticles);
        ~ParticleGun();

        void SetParticleMomentum(G4double aMomentum, bool verbose);
        void SetParticleMomentum(G4ParticleMomentum aMomentum, bool verbose);
};

#endif