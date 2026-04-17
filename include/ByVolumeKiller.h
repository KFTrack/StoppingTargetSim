// Ed Callaghan
// Kill tracks if a step enters forbidden volumes
// April 2026

#ifndef BYVOLUMEKILLER_H
#define BYVOLUMEKILLER_H

#include <G4Navigator.hh>
#include <G4LogicalVolume.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4Step.hh>
#include <G4TrackStatus.hh>
#include <G4TransportationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VPhysicalVolume.hh>

class ByVolumeKiller: public G4UserSteppingAction{
  public:
    ByVolumeKiller();
   ~ByVolumeKiller();

    void AddVolume(const std::string volume);

    void UserSteppingAction(const G4Step* step);

  protected:
    bool initialized;
    std::vector<std::string> names;
    std::vector<G4VPhysicalVolume*> volumes;
    G4Navigator* navigator;

    bool is_contained(const G4ThreeVector& position,
                      const G4VPhysicalVolume* volume);

    void initialize_volume_fields();

  private:
    /**/
};

#endif
