// Teja Nivarthi
// User-level detector construction parser
// December 2023

#include <G4VSolid.hh>
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Box.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Tubs.hh>
#include <G4Sphere.hh>

#include <YamlParser.h>
#include <unordered_map>
using namespace std;

class StoppingTargetConfigParser {
    public:
      StoppingTargetConfigParser(G4LogicalVolume* _world_log);
     ~StoppingTargetConfigParser();

     void CreateSolid(const YamlNode& config);
    protected:
    /**/
    private:
      G4LogicalVolume* world_log;
      G4NistManager* nist;
      
      G4VSolid* getVSolid(string shape, const YamlNode& parameters);
      G4LogicalVolume* getLogVolume(const YamlNode& param_node, G4VSolid* solid);
      void placeSolid(const YamlNode& param_node, G4LogicalVolume* log_volume);

      // template<typename T>
      // T* constructor(const YamlNode& node);

      G4VSolid* constructorBoxVSolid(const YamlNode& paramNode);
      G4VSolid* constructorSphereVSolid(const YamlNode& paramNode);
      G4VSolid* constructorTubsVSolid(const YamlNode& paramNode);


};