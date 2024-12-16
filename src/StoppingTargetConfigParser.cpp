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
    } else if(name == "custom") {
        rv = constructorBoundedPlane(params);
    } else {
        // Error out
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

G4VSolid* StoppingTargetConfigParser::constructorBoundedPlane(const YamlNode& paramNode) {
    G4MultiUnion* combinedPrism = nullptr;
    // G4TessellatedSolid* combinedPrism = new G4TessellatedSolid("CombinedSolid"); 
    G4VSolid* rv = nullptr;
    YamlNode params = YamlNode(paramNode);
    double THICKNESS = 10 * CLHEP::mm; // [m]

    cout << "bounded planes" << endl;

    vector<G4ThreeVector> aPoints;
    YamlNode aPointsList = params["a"];
    LoadPoints(aPointsList, &aPoints);

    vector<G4ThreeVector> bPoints;
    YamlNode bPointsList = params["b"];
    LoadPoints(bPointsList, &bPoints);

    int numPoints = aPoints.size();

    // Corners of triangle
    G4ThreeVector a1, a2, b1, b2;
    G4ThreeVector translation1, translation2;
    G4RotationMatrix rotation1, rotation2;
    G4Transform3D transform1, transform2;

    combinedPrism = new G4MultiUnion("Triangles_Combined");

    for (int i = 0; i < numPoints-1; i++) {
        a1 = aPoints.at(i);
        a2 = aPoints.at(i+1);
        b1 = bPoints.at(i);
        b2 = bPoints.at(i+1);

        G4VSolid* prism1 = constructorTriangularPlane(a1, a2, b1, THICKNESS);
        G4VSolid* prism2 = constructorTriangularPlane(b1, b2, a2, THICKNESS);

        translation1 = a1-G4ThreeVector(0.0001, 0.0001, 0.0001);
        translation2 = b1-(0.001)*a1;

        rotation1 = G4RotationMatrix();
        rotation2 = G4RotationMatrix();
        CalculateBasisAndRotation(a1, a2, b1, rotation1);
        CalculateBasisAndRotation(b1, b2, a2, rotation2);

        transform1 = G4Transform3D(rotation1, translation1);
        transform2 = G4Transform3D(rotation2, translation2);

        combinedPrism->AddNode(prism1, transform1);
        combinedPrism->AddNode(prism2, transform2);
    }

    combinedPrism->Voxelize();

    rv = combinedPrism;
    return rv;

}

void StoppingTargetConfigParser::LoadPoints(const YamlNode& pointsNode, vector<G4ThreeVector>* pointsList) {
    YamlNode points = YamlNode(pointsNode);
    G4ThreeVector curPoint;

    double x, y, z;
    string xFmt, yFmt, zFmt;

    for (auto point: points) {
        cout << point << endl;
        x = YamlNode(point[0]).Value<double>() * CLHEP::m;
        y = YamlNode(point[1]).Value<double>() * CLHEP::m;
        z = YamlNode(point[2]).Value<double>() * CLHEP::m;

        curPoint = G4ThreeVector(x, y, z);
        pointsList->insert(pointsList->begin(), curPoint);
    }
}

void StoppingTargetConfigParser::CalculateBasisAndRotation(G4ThreeVector a, G4ThreeVector b, G4ThreeVector c, G4RotationMatrix& rotation) {
    // G4RotationMatrix* rotation = new G4RotationMatrix;

    G4ThreeVector AB = b-a;
    G4ThreeVector AC = c-a;

    G4ThreeVector N = AB.cross(AC); // Normal vector to the plane of the triangle
    G4ThreeVector n = N.unit(); // Unit normal vector
    G4ThreeVector u = AB.unit(); // Unit vector of one basis vector, ** The Privilaged Unit Vector **
    G4ThreeVector V = n.cross(u); 
    G4ThreeVector v = V.unit(); // 3rd orthogonal basis vector of the set (u, v, n)

    rotation.rotateAxes(u, v, n);
 
    // return rotation;
    return;
}

G4VSolid* StoppingTargetConfigParser::constructorTriangularPlane(G4ThreeVector a1, G4ThreeVector a2, G4ThreeVector b1, double thickness) {
    /** Triangular plane will be constructed using a1 as (0, 0) */

    G4VSolid* rv = nullptr;
    cout << "triangle" << endl;

    // Define coordinates relative to a1. Making a = (0, 0, 0)
    G4ThreeVector a(0, 0, 0);
    G4ThreeVector b = a2 - a1;
    G4ThreeVector c = b1 - a1;

    // Privilaged vector AB will be our reference 
    G4ThreeVector AB = b;  // a -> b or a1 -> a2
    G4ThreeVector AC = c; // a -> c or a1 -> b1

    // Construct orthogonal basis from triangle
    G4ThreeVector N = AB.cross(AC); // Normal vector to the plane of the triangle
    G4ThreeVector n = N.unit(); // Unit normal vector
    G4ThreeVector u = AB.unit(); // Unit vector of one basis vector, ** The Privilaged Unit Vector **
    G4ThreeVector V = n.cross(u); 
    G4ThreeVector v = V.unit(); // 3rd orthogonal basis vector of the set (u, v, n)

    // Construct triangle in 2D plane
    std::vector<G4TwoVector> triangle(3);
    triangle[0] = G4TwoVector(a.dot(u), a.dot(v));
    triangle[1] = G4TwoVector(b.dot(u), b.dot(v));    
    triangle[2] = G4TwoVector(c.dot(u), c.dot(v));

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;

    cout << "u: " << u << endl;
    cout << "v: " << v << endl;
    cout << "n: " << n << endl;

    cout << "triangle 1: " << triangle[0] << endl;
    cout << "triangle 2: " << triangle[1] << endl;
    cout << "triangle 3: " << triangle[2] << endl;

    cout << "\n" << endl;

    rv = new G4ExtrudedSolid("Prism", triangle, thickness/2, G4TwoVector(0,0), 1., G4TwoVector(0,0), 1.);


    // // Determine rotation required about v-axis to go from 2d space into 3d
    // G4ThreeVector a_prime = G4TwoVector(a.dot(u), a.dot(v), 0);
    // G4ThreeVector b_prime = G4TwoVector(b.dot(u), b.dot(v), 0);
    // G4ThreeVector c_prime = G4TwoVector(c.dot(u), c.dot(v), 0);

    // define a privilages point and side as our reference side (p4esoint a and side x = ab).
    // when we place our original triangle into a 2d basis, we have a -> a' , x -> x' (side a'b')
    // we define a' = (0, 0, 0). translation is as simple as moving to where a is located
    // rotation is defined by determining a.dot(a') and rotating about x.cross(x') up to a sign
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
    cout << "got solid" << endl;
    G4LogicalVolume* log_volume = getLogVolume(node, solid);
    cout << "fin log vol" << endl;
    G4RotationMatrix* rot = getRotation(node);
    cout << "fin rot" << endl;
    placeSolid(node, log_volume, rot);
    cout << "placed solid" << endl;
}
