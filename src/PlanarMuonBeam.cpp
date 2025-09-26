// Teja Nivarthi
// Planar, monoenergetic muon beam
// April 2024

#include <PlanarMuonBeam.h>

PlanarMuonBeam::PlanarMuonBeam(G4ThreeVector position, G4ThreeVector momentum){
    this->position = position;
    this->momentum = momentum;
}

PlanarMuonBeam::~PlanarMuonBeam(){
    /**/
}

void PlanarMuonBeam::SampleMuonState(){
    double newX, newY;
    double r, theta;

    // double Rmin = 21.5;
    double Rmin = 0;
    double Rmax = 75.0;

    double Umin = pow(Rmin, 2) / 2;
    double Umax = pow(Rmax, 2) / 2;

    theta = G4UniformRand() * 2 * CLHEP::pi;
    r = pow(2 * G4UniformRand() * (Umax - Umin) + Umin, 0.5);

    newX = r * cos(theta) * CLHEP::mm;
    newY = r * sin(theta) * CLHEP::mm;
    // newX = (G4UniformRand() * 10 - 5) * CLHEP::m;
    // newY = (G4UniformRand() * 10 - 5) * CLHEP::m;
    // std::cout << newX << " " << newY << std::endl;
    G4ThreeVector newPosition(newX, newY, 0.0 * CLHEP::mm);
    this->position = newPosition;
}