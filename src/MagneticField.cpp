// Teja Nivarthi
// User-level Magnetic field definition
// May 2024

#include <MagneticField.h>
using namespace std;

MagneticField::MagneticField() : G4MagneticField() {}

MagneticField::~MagneticField() {};

void MagneticField::GetFieldValue(const G4double point[4], G4double *bField) const
{
    G4double fBz = 0;

    if ((point[2] >= 0) && (point[2] < 2*CLHEP::m)) {
        fBz = 2 - (point[2] * 0.0005);
    }

    bField[0] = 0;
    bField[1] = 0;
    bField[2] = fBz * CLHEP::tesla;
}