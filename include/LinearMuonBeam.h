// Ed Callaghan
// Perfectly colinear, monoenergetic muon beam
// April 2024

#ifndef LINEARMUONBEAM_H
#define LINEARMUONBEAM_H

#include <MuonBeam.h>

class LinearMuonBeam: public MuonBeam{
  public:
    LinearMuonBeam(G4ThreeVector position, G4ThreeVector momentum);
   ~LinearMuonBeam();

    void SampleMuonState();
  protected:
    /**/
  private:
    /**/
};

#endif
