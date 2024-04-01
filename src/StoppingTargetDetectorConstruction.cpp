// Ed Callaghan
// User-level detector construction
// November 2023

#include <StoppingTargetDetectorConstruction.h>
using namespace std;

StoppingTargetDetectorConstruction::StoppingTargetDetectorConstruction(){
    /**/
}

StoppingTargetDetectorConstruction::~StoppingTargetDetectorConstruction(){
    /**/
}

StoppingTargetDetectorConstruction::StoppingTargetDetectorConstruction(const YamlNode& node) {
    parameters = YamlNode(node);
}

G4VPhysicalVolume* StoppingTargetDetectorConstruction::ConstructCustom(){
    // TODO: Read in macro file, 
    // determine world size
    // determine relative positions (mother-daughter structure) using nested values in macro file
    // determine materials, shapes, etc within 

    YamlNode detectorNode = YamlNode(parameters);

    CreateWorldLog();
    auto parser = StoppingTargetConfigParser(world_log);

   for (auto child: detectorNode) {
       cout << child << endl;
       parser.CreateSolid(child);
   }
    
    G4ThreeVector origin(0.0, 0.0, 0.0);
    G4VPhysicalVolume* world_phys = new G4PVPlacement(0, origin, world_log, "world", NULL, false, 0);
    return world_phys;
}

void StoppingTargetDetectorConstruction::CreateWorldLog(){
    double _dim = 5;
    G4NistManager* nist = G4NistManager::Instance();

    // Move to detector construction
    double dim = _dim * CLHEP::m;

    G4Material* world_material = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* world_solid = new G4Box("world", dim, dim, dim);
    
    world_log = new G4LogicalVolume(world_solid, world_material, "world"); 
}

G4VPhysicalVolume* StoppingTargetDetectorConstruction::Construct(){
    // double dim = 2.0 * CLHEP::m;
    // G4ThreeVector origin(0.0, 0.0, 0.0);
    // G4ThreeVector foilVec(0.0, 0.0, 0.5*CLHEP::m);
    // G4NistManager* nist = G4NistManager::Instance();

    // G4Material* world_material = nist->FindOrBuildMaterial("G4_AIR");
    // G4Box* world_solid = new G4Box("world", dim, dim, dim);
    // G4LogicalVolume* world_log = new G4LogicalVolume(world_solid, world_material, "world");
    // G4VPhysicalVolume* world_phys = new G4PVPlacement(0, origin, world_log, "world", NULL, false, 0);


    // G4Material* foil_material = nist->FindOrBuildMaterial("G4_Al");
    // // Foil should have hole in the center. no hole now for testing purposes and should be 100 um
    // G4Tubs* foil_solid = new G4Tubs("foil", 0, 7.1859*CLHEP::cm, 100*CLHEP::cm, 0*CLHEP::deg, 360*CLHEP::deg);
    // G4LogicalVolume* foil_log = new G4LogicalVolume(foil_solid, foil_material, "foil");
    // G4VPhysicalVolume* foil_phys = new G4PVPlacement(0, foilVec, foil_log, "foil", world_log, false, 0);

    // G4VPhysicalVolume* rv = world_phys;
    // return rv;

    G4VPhysicalVolume* rv = ConstructCustom();
    return rv;
}
