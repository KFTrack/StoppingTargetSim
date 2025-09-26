// Teja Nivarthi
// User-level Magnetic field definition
// May 2024

#ifndef MAGNETICFIELD_H
#define MAGNETICFIELD_H

#include <G4MagneticField.hh>
#include <CLHEP/Units/SystemOfUnits.h>

class MagneticField: public G4MagneticField {

    public:
        MagneticField();
        ~MagneticField();
        
        virtual void GetFieldValue(const G4double point[4], G4double *bField) const override;

};

#endif
