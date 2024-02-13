// Ed Callaghan
// User-level detector construction
// November 2023

#ifndef STOPPINGTARGETDETECTORCONSTRUCTION_H
#define STOPPINGTARGETDETECTORCONSTRUCTION_H

// G4 libraries
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Box.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Tubs.hh>

// Other libraries
#include <YamlParser.h>
#include <StoppingTargetConfigParser.h>

class StoppingTargetDetectorConstruction: public G4VUserDetectorConstruction{
  public:
    StoppingTargetDetectorConstruction();
    StoppingTargetDetectorConstruction(const YamlNode& node);
   ~StoppingTargetDetectorConstruction();

    void CreateWorldLog();
    G4VPhysicalVolume* ConstructCustom();
    G4VPhysicalVolume* Construct();
  protected:
    /**/
  private:
    G4LogicalVolume* world_log;
    YamlNode parameters;
};

#endif
