// Ed Callaghan
// Perfectly colinear, monoenergetic muon beam
// April 2024

#include <LinearMuonBeam.h>

LinearMuonBeam::LinearMuonBeam(G4ThreeVector position, G4ThreeVector momentum){
    this->position = position;
    this->momentum = momentum;
}

LinearMuonBeam::~LinearMuonBeam(){
    /**/
}

void LinearMuonBeam::SampleMuonState(){
    // do nothing
}
