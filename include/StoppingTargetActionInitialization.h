// Ed Callaghan
// User-level action initialization
// October 2023

#include <G4VUserActionInitialization.hh>
#include <StoppingTargetPrimaryGeneratorAction.h>

class StoppingTargetActionInitialization: public G4VUserActionInitialization{
  public:
    StoppingTargetActionInitialization();
   ~StoppingTargetActionInitialization();

    // instantiate / register subclasses of the following:
    // G4VUserPrimaryGeneratorAction: specify primary particles
    // G4UserRunAction              : begin-/end-of-run bookkeeping
    // G4UserEventAction            : begin-/end-of-event bookkeeping
    // G4UserStackingAction         : details of track stacking
    // G4UserTrackingAction         : begin-/end-of-track actions / bookkeeping
    // G4UserSteppingAction         : end-of-step actions / bookkeeping
    void Build() const;

  protected:
  	/**/
  private:
  	/**/
};
