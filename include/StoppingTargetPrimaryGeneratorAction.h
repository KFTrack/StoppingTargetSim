// Ed Callaghan
// User-level primary generator action
// October 2023

#include <G4VUserPrimaryGeneratorAction.hh>

class StoppingTargetPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{
  public:
    StoppingTargetPrimaryGeneratorAction();
   ~StoppingTargetPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

  protected:
  	/**/
  private:
  	/**/
};
