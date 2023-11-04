// Ed Callaghan
// User-level detector construction
// November 2023

#include <G4VUserDetectorConstruction.hh>

class StoppingTargetDetectorConstruction: public G4VUserDetectorConstruction{
  public:
    StoppingTargetDetectorConstruction();
   ~StoppingTargetDetectorConstruction();

    G4VPhysicalVolume* Construct();
  protected:
    /**/
  private:
    /**/
};
