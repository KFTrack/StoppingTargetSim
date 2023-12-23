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

StoppingTargetDetectorConstruction::StoppingTargetDetectorConstruction(const YamlNode& detectorNode){
    
    auto parser = StoppingTargetConfigParser(5);

    for (auto child: detectorNode) {
        parser.CreateBooleanSolid(child);
        // string name = YamlNode(child)["name"].Value<string>();
        // string units = YamlNode(child)["units"].Value<string>();
        // unsigned int dim = YamlNode(child)["dim"].Value<unsigned int>();
        // printf("%s with side length %d %s\n", name.c_str(), dim, units.c_str());
    }
}

G4VPhysicalVolume* StoppingTargetDetectorConstruction::ConstructCustom(){
    // TODO: Read in macro file, 
    // determine world size
    // determine relative positions (mother-daughter structure) using nested values in macro file
    // determine materials, shapes, etc within 
    return NULL;
}

G4VPhysicalVolume* StoppingTargetDetectorConstruction::Construct(){
    double dim = 2.0 * CLHEP::m;
    G4ThreeVector origin(0.0, 0.0, 0.0);
    G4ThreeVector foilVec(0.0, 0.0, 0.5*CLHEP::m);
    G4NistManager* nist = G4NistManager::Instance();

    G4Material* world_material = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* world_solid = new G4Box("world", dim, dim, dim);
    G4LogicalVolume* world_log = new G4LogicalVolume(world_solid, world_material, "world");
    G4VPhysicalVolume* world_phys = new G4PVPlacement(0, origin, world_log, "world", NULL, false, 0);


    G4Material* foil_material = nist->FindOrBuildMaterial("G4_Al");
    // Foil should have hole in the center. no hole now for testing purposes and should be 100 um
    G4Tubs* foil_solid = new G4Tubs("foil", 0, 7.1859*CLHEP::cm, 100*CLHEP::cm, 0*CLHEP::deg, 360*CLHEP::deg);
    G4LogicalVolume* foil_log = new G4LogicalVolume(foil_solid, foil_material, "foil");
    G4VPhysicalVolume* foil_phys = new G4PVPlacement(0, foilVec, foil_log, "foil", world_log, false, 0);

    G4VPhysicalVolume* rv = world_phys;
    return rv;
}
