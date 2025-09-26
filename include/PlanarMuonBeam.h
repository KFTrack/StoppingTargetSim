// Teja Nivarthi
// Perfectly planar, monoenergetic muon beam
// April 2024

#ifndef PLANARMUONBEAM_H
#define PLANARMUONBEAM_H

#include <MuonBeam.h>
#include <CLHEP/Random/RandFlat.h>
#include <CLHEP/Random/RandomEngine.h>
#include <CLHEP/Random/Random.h>
#include <Randomize.hh>
#include <CLHEP/Units/PhysicalConstants.h>
#include <math.h>

class PlanarMuonBeam: public MuonBeam{
  public:
    PlanarMuonBeam(G4ThreeVector position, G4ThreeVector momentum);
   ~PlanarMuonBeam();

    void SampleMuonState();
  protected:
    /**/
  private:
    /**/
};

#endif