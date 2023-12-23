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
#include <G4Tubs.hh>

#include <YamlParser.h>
#include <unordered_map>
using namespace std;

class StoppingTargetConfigParser {
    public:
      StoppingTargetConfigParser(double _dim);
     ~StoppingTargetConfigParser();

      struct BOXData { string pName; int pLen; };
      struct SPHEREData { string pName; int pRad; };

      enum SOLID_SHAPE
      {
          BOX,
          SPHERE,
          TUBS
      };

     G4VSolid* CreateBooleanSolid(const YamlNode& config);
    protected:
    /**/
    private:
      G4LogicalVolume* world_log;
      G4NistManager* nist;
      
      G4VSolid* getVSolid(string shape, const YamlNode& parameters);

      template<typename T>
      T* constructor(YamlNode node);
      
      G4VSolid* defineBox(const YamlNode& param);
      G4VSolid* defineSphere(const YamlNode& params);

};