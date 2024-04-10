// Ed Callaghan
// Base class for one-at-a-time muon beams
// April 2024

#ifndef MUONBEAM_H
#define MUONBEAM_H

// G4 includes
#include <G4ParticleTable.hh>
#include <G4ParticleGun.hh>

// other
#include <EventGenerator.h>

class MuonBeam: public EventGenerator{
  public:
    MuonBeam();
   ~MuonBeam();

    virtual void GeneratePrimaries(G4Event*);

    // override this to sample new position/momentum, and store in members
    virtual void SampleMuonState() = 0;
  protected:
    G4ParticleGun* gun;
    G4ThreeVector position;
    G4ThreeVector momentum;
  private:
    /**/
};

#endif
