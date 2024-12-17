// Ed Callaghan
// Monoenergetic electrons sampled spatially from within a G4 volume
// October 2024

#ifndef MonoenergeticElectronsInVolume_h
#define MonoenergeticElectronsInVolume_h

// stl
#include <string>

// CLHEP
#include <CLHEP/Units/GlobalPhysicalConstants.h>

// G4 includes
#include <G4AffineTransform.hh>
#include <G4LogicalVolume.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleGun.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>
#include <G4TransportationManager.hh>
#include <G4Navigator.hh>
#include <G4VoxelLimits.hh>
#include <Randomize.hh>

// other
#include <EventGenerator.h>

class MonoenergeticElectronsInVolume: public EventGenerator{
  public:
    MonoenergeticElectronsInVolume(double, std::string);
   ~MonoenergeticElectronsInVolume();

    virtual void GeneratePrimaries(G4Event*);

    virtual void SampleElectronState();
  protected:
    G4ParticleGun* gun;
    G4ThreeVector position;
    G4ThreeVector momentum;

    bool initialized;
    std::string volume_name;
    G4VPhysicalVolume* volume;
    G4AffineTransform global;
    G4Navigator* navigator;
    double xmin, xmax;
    double ymin, ymax;
    double zmin, zmax;

    double energy;
    double momentum_magnitude;

    void initialize_volume_fields();
  private:
    /**/
};

#endif
