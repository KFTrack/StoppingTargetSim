// Ed Callaghan
// User-level primary generator action
// October 2023

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleGun.hh>

class StoppingTargetPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{
  public:
    StoppingTargetPrimaryGeneratorAction();
   ~StoppingTargetPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);
  protected:
  	/**/
    G4ParticleGun* gun;
  private:
  	/**/
};
