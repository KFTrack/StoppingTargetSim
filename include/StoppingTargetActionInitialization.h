// Ed Callaghan
// User-level action initialization
// October 2023

#ifndef STOPPINGTARGETACTIONINITIALIZATION_H
#define STOPPINGTARGETACTIONINITIALIZATION_H

#include <iostream>
#include <G4VUserActionInitialization.hh>
#include <StoppingTargetPrimaryGeneratorAction.h>
#include <TrackBookkeeper.h>
#include <ASCIITrackingSink.h>

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

#endif
