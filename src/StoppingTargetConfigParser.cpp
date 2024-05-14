// Teja Nivarthi
// User-level detector construction parser
// December 2023

#include <StoppingTargetConfigParser.h>
using namespace std;

StoppingTargetConfigParser::StoppingTargetConfigParser(G4LogicalVolume* _world_log){
    nist = G4NistManager::Instance();
    world_log = _world_log;
}

StoppingTargetConfigParser::~StoppingTargetConfigParser(){
    /**/
}

G4VSolid* StoppingTargetConfigParser::getVSolid(string name, const YamlNode& parameters) {
    YamlNode params = YamlNode(parameters);
    G4VSolid* rv;

    // change to switch statement
    if (name == "box") {
        // cout << "box" << endl;
        rv = constructorBoxVSolid(params);
    } else if(name == "sphere") {
        // cout << "sphere" << endl;
        rv = constructorSphereVSolid(params);
    } else if(name == "tube") {
        // cout << "tube" << endl;
        rv = constructorTubsVSolid(params);
    }

    return rv;
}

G4VSolid* StoppingTargetConfigParser::constructorBoxVSolid(const YamlNode& paramNode) {
    G4VSolid* rv = nullptr;
    YamlNode params = YamlNode(paramNode);
    
    string pName = params["pName"].Value<string>();
    double pX = params["pX"].Value<double>() * CLHEP::m;
    double pY = params["pY"].Value<double>() * CLHEP::m;
    double pZ = params["pZ"].Value<double>() * CLHEP::m;
    
    rv = new G4Box(pName, pX, pY, pZ);
    return rv;
}

G4VSolid* StoppingTargetConfigParser::constructorSphereVSolid(const YamlNode& paramNode) {
    G4VSolid* rv = nullptr;
    YamlNode params = YamlNode(paramNode);
    
    string pName = params["pName"].Value<string>();
    double pRmin = params["pRmin"].Value<double>() * CLHEP::m;
    double pRmax = params["pRmax"].Value<double>() * CLHEP::m;
    double pSPhi = params["pSPhi"].Value<double>() * CLHEP::deg;
    double pDPhi = params["pDPhi"].Value<double>() * CLHEP::deg;
    double pSTheta = params["pSTheta"].Value<double>() * CLHEP::deg;
    double pDTheta = params["pDTheta"].Value<double>() * CLHEP::deg;

    rv = new G4Sphere(pName, pRmin, pRmax, pSPhi, pDPhi, pSTheta, pDTheta);
    return rv;
}

G4VSolid* StoppingTargetConfigParser::constructorTubsVSolid(const YamlNode& paramNode) {
    G4VSolid* rv = nullptr;
    YamlNode params = YamlNode(paramNode);
    
    string pName = params["pName"].Value<string>();
    double pRmin = params["pRmin"].Value<double>() * CLHEP::m;
    double pRmax = params["pRmax"].Value<double>() * CLHEP::m;
    double pDz = params["pDz"].Value<double>() * CLHEP::m;
    double pSPhi = params["pSPhi"].Value<double>() * CLHEP::deg;
    double pDPhi = params["pDPhi"].Value<double>() * CLHEP::deg;

    rv = new G4Tubs(pName, pRmin, pRmax, pDz, pSPhi, pDPhi);
    return rv;
}


G4LogicalVolume* StoppingTargetConfigParser::getLogVolume(const YamlNode& param_node, G4VSolid* solid) {
    G4LogicalVolume* rv = nullptr;
    YamlNode node = YamlNode(param_node);

    string mat_str = node["material"].Value<string>();
    string name = node["type"].Value<string>();
    double density = node["density"].Value<double>()  * CLHEP::g / CLHEP::cm3;

    G4Material* material = nist->FindOrBuildMaterial(mat_str);

    G4Material* env_mat = new G4Material("Custom Aluminum", 13.00, 26.981539, density=density);

    // cout << "MATERIAL FOR BOX SYNTHETIC: " << env_mat << endl;
    // cout << "MATERIAL FOR BOX REAL: " << material << endl;
    
    rv = new G4LogicalVolume(solid, env_mat, name);
    return rv;
}

void StoppingTargetConfigParser::placeSolid(const YamlNode& param_node, G4LogicalVolume* log_volume, G4RotationMatrix* rotMat) {
    YamlNode pos_node = YamlNode(param_node)["position"];
    string name = YamlNode(param_node)["parameters"]["pName"].Value<string>();

    double posX = pos_node["x"].Value<double>() * CLHEP::m;
    double posY = pos_node["y"].Value<double>() * CLHEP::m;
    double posZ = pos_node["z"].Value<double>() * CLHEP::m;

    G4ThreeVector posVec(posX, posY, posZ);

    // Still need to implement rotation and whatever the last 2 parameters of the below function are
    G4VPhysicalVolume* phys = new G4PVPlacement(rotMat, posVec, log_volume, name, world_log, false, 0);
}

G4RotationMatrix* StoppingTargetConfigParser::getRotation(const YamlNode& param_node) {
    double x_ang = 0, y_ang = 0, z_ang = 0;

    YamlNode params = YamlNode(param_node);
    
    if (params.has_child("rotation")) {
        YamlNode node = params["rotation"];

        x_ang = node["x"].Value<double>() * CLHEP::deg;
        y_ang = node["y"].Value<double>() * CLHEP::deg;
        z_ang = node["z"].Value<double>() * CLHEP::deg;
    }

    G4RotationMatrix* rot = new G4RotationMatrix;

    rot->rotateX(x_ang);
    rot->rotateY(y_ang);
    rot->rotateZ(z_ang);

    return rot;
}

void StoppingTargetConfigParser::CreateSolid(const YamlNode& config) {
    YamlNode node = YamlNode(config);
    // cout << node << endl;

    // int pos = node["position"].Value<int>();
    string material = node["material"].Value<string>();
    string type_str = node["type"].Value<string>();

    printf("type: %s, material: %s\n", type_str.c_str(), material.c_str());

    G4VSolid* solid = getVSolid(type_str, node["parameters"]);
    G4LogicalVolume* log_volume = getLogVolume(node, solid);
    G4RotationMatrix* rot = getRotation(node);
    placeSolid(node, log_volume, rot);
}
