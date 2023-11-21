// Ed Callaghan
// G4 example main file
// November 2023

#ifndef STOPPINGTARGETPHYSICSLIST_H
#define STOPPINGTARGETPHYSICSLIST_H

#include <G4VUserPhysicsList.hh>
#include <G4BosonConstructor.hh>
#include <G4LeptonConstructor.hh>
#include <G4PhysicsListHelper.hh>
#include <G4ParticleDefinition.hh>
#include <G4Gamma.hh>
#include <G4Electron.hh>
//#include <G4Muon.hh>

class StoppingTargetPhysicsList: public G4VUserPhysicsList{
  public:
    StoppingTargetPhysicsList();
   ~StoppingTargetPhysicsList();

    void ConstructParticle();
    void ConstructProcess();

    // void SetCets();

  protected:
    /**/
  private:
    /**/
};

#endif
