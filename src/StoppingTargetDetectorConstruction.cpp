// Ed Callaghan
// User-level detector construction
// November 2023

#include <StoppingTargetDetectorConstruction.h>
#include <G4Sphere.hh>
#include <CLHEP/Units/GlobalPhysicalConstants.h>

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

    G4Box* box = new G4Box("box", 0.9 * dim, 0.9 * dim, 0.9 * dim);
    G4LogicalVolume* box_log = new G4LogicalVolume(box, world_material, "box");
    G4VPhysicalVolume* box_phys = new G4PVPlacement(0, origin, box_log, "box", world_log, false, 0);

    G4Box* inner_box = new G4Box("inner_box", 0.8 * dim, 0.8 * dim, 0.8 * dim);
    G4LogicalVolume* inner_box_log = new G4LogicalVolume(inner_box, world_material, "inner_box");
    G4VPhysicalVolume* inner_box_phys = new G4PVPlacement(0, origin, inner_box_log, "inner_box", box_log, false, 0);

    G4VPhysicalVolume* rv = world_phys;
    this->world = world_log;
    return rv;
}

G4LogicalVolume* StoppingTargetDetectorConstruction::GetWorld(){
    auto rv = this->world;
    return rv;
}
