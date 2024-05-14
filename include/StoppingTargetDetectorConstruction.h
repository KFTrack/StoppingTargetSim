// Ed Callaghan
// User-level detector construction
// November 2023

#ifndef STOPPINGTARGETDETECTORCONSTRUCTION_H
#define STOPPINGTARGETDETECTORCONSTRUCTION_H

#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Box.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4VPhysicalVolume.hh>

class StoppingTargetDetectorConstruction: public G4VUserDetectorConstruction{
  public:
    StoppingTargetDetectorConstruction();
   ~StoppingTargetDetectorConstruction();

    G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetWorld();
  protected:
    G4LogicalVolume* world;
  private:
    /**/
};

#endif
