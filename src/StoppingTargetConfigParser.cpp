// Teja Nivarthi
// User-level detector construction parser
// December 2023

#include <StoppingTargetConfigParser.h>
using namespace std;

StoppingTargetConfigParser::StoppingTargetConfigParser(double dim){
    // Move to detector construction
    dim = dim * CLHEP::m;

    nist = G4NistManager::Instance();
    G4Material* world_material = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* world_solid = new G4Box("world", dim, dim, dim);
    
    world_log = new G4LogicalVolume(world_solid, world_material, "world"); 

    // std::map[SOLID_SHAPE::BOX]=G4Box;
}

StoppingTargetConfigParser::~StoppingTargetConfigParser(){
    /**/
}

G4VSolid* StoppingTargetConfigParser::getVSolid(string name, const YamlNode& parameters) {
    SOLID_SHAPE shape = SOLID_SHAPE::BOX;
    YamlNode params = YamlNode(parameters);
    G4VSolid* rv;

    // change to switch statement
    if (!name.compare("box")) {
        BOXData ptr;
        ptr.pName = params["pName"].Value<string>();
        ptr.pLen = params["pLen"].Value<int>();
        // rv = new G4Box(ptr);

    } else if(!name.compare("sphere")) {
        SPHEREData ptr;
        ptr.pName = params["pName"].Value<string>();
        ptr.pRad = params["pRad"].Value<int>();
        // rv = new G4Sphere(ptr);
    }

    return nullptr;
    //stl map
}

template<typename T>
T* constructor(YamlNode node) {
    T* rv = new T;
    return rv;
    // look into variatic function arguments
}

G4VSolid* StoppingTargetConfigParser::CreateBooleanSolid(const YamlNode& config) {
    YamlNode node = YamlNode(config);

    int pos = node["position"].Value<int>();
    string material = node["material"].Value<string>();
    string type_str = node["type"].Value<string>();

    printf("type: %s, position: %d, material: %s\n", type_str.c_str(), pos, material.c_str());

    G4VSolid* solid = getVSolid(type_str, node["parameters"]);

    return nullptr;
}