// Teja Nivarthi
// User-level Magnetic field definition
// May 2024

#include <MagneticField.h>
using namespace std;

MagneticField::MagneticField() : G4MagneticField() {}

MagneticField::~MagneticField() {};

void MagneticField::GetFieldValue(const G4double point[4], G4double *bField) const
{
    G4double intercept = 0.5488564880705443 * CLHEP::tesla; 
    G4double offset = -6070 * CLHEP::mm;
    G4double gradient = -0.00021831590974124085 * (CLHEP::tesla/CLHEP::mm);
    G4double upperbound = 2500;
    G4double lowerbound = 0;

    G4double z = point[2];
    G4double fBz;

    if ((z < lowerbound)) {
 	fBz = intercept + (lowerbound+offset)*gradient;
    }
    else if ((z < upperbound)) {
	fBz = intercept + (z+offset)*gradient;
    }
    else if ((z >= upperbound)) {
	fBz = intercept + (upperbound+offset)*gradient;
    }

    bField[0] = 0;
    bField[1] = 0;
    bField[2] = fBz * CLHEP::tesla;
}
