// Ed Callaghan
// G4 example main file
// November 2023

#include <G4VUserPhysicsList.hh>

class StoppingTargetPhysicsList: public G4VUserPhysicsList{
  public:
    StoppingTargetPhysicsList();
   ~StoppingTargetPhysicsList();

    void ConstructParticle();
    void ConstructProcess();

  protected:
    /**/
  private:
    /**/
};
