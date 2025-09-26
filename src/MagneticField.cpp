// Teja Nivarthi
// User-level Magnetic field definition
// May 2024

#include <MagneticField.h>
using namespace std;

MagneticField::MagneticField() : G4MagneticField() {}

MagneticField::~MagneticField() {};

void MagneticField::GetFieldValue(const G4double point[4], G4double *bField) const
{
    G4double fBz = 2;

    G4double length = 5.2969 * CLHEP::m;
    G4double gradient = -1 / length;

    if ((point[2] >= 0) && (point[2] < length)) {
        fBz = 2 + (point[2] * gradient);
    }

    bField[0] = 0;
    bField[1] = 0;
    bField[2] = fBz * CLHEP::tesla;
}