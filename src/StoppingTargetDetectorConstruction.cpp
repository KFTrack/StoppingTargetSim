// Ed Callaghan
// User-level detector construction
// November 2023

#include <StoppingTargetDetectorConstruction.h>

StoppingTargetDetectorConstruction::StoppingTargetDetectorConstruction(){
    /**/
}

StoppingTargetDetectorConstruction::~StoppingTargetDetectorConstruction(){
    /**/
}

G4VPhysicalVolume* StoppingTargetDetectorConstruction::Construct(){
    double dim = 10.0 * CLHEP::m;
    G4ThreeVector origin(0.0, 0.0, 0.0);
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* world_material = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* world_solid = new G4Box("world", dim, dim, dim);
    G4LogicalVolume* world_log = new G4LogicalVolume(world_solid, world_material, "world");
    G4VPhysicalVolume* world_phys = new G4PVPlacement(0, origin, world_log, "world", NULL, false, 0);

    G4VPhysicalVolume* rv = world_phys;
    this->world = world_log;
    return rv;
}

G4LogicalVolume* StoppingTargetDetectorConstruction::GetWorld(){
    auto rv = this->world;
    return rv;
}
