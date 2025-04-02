// Ed Callaghan
// Monoenergetic electrons sampled spatially from within multiple G4 volumes
// April 2025

#ifndef MonoenergeticElectronsInVolumes_h
#define MonoenergeticElectronsInVolumes_h

// stl
#include <string>
#include <vector>

// G4 includes
#include <G4LogicalVolume.hh>
#include <G4PhysicalVolumeStore.hh>
#include <Randomize.hh>

// other
#include <EventGenerator.h>
#include <MonoenergeticElectronsInVolume.h>

class MonoenergeticElectronsInVolumes: public EventGenerator{
  public:
    MonoenergeticElectronsInVolumes(double, std::vector<std::string>);
   ~MonoenergeticElectronsInVolumes();

    virtual void GeneratePrimaries(G4Event*);
  protected:
    std::vector<std::string> volume_names;
    std::vector<double> weights;
    std::vector<double> cumulative_weights;
    std::vector<MonoenergeticElectronsInVolume> generators;

    bool initialized;
    void initialize_weights();

  private:
    /**/
};

#endif
