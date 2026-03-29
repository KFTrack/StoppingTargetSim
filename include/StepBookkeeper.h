// Ed Callaghan
// User-level stepping actions
// March 2026

#ifndef STEPBOOKKEEPER_H
#define STEPBOOKKEEPER_H

#include <G4Step.hh>
#include <G4UserSteppingAction.hh>
#include <TrackingSink.h>

class StepBookkeeper: public G4UserSteppingAction{
  public:
    StepBookkeeper();
   ~StepBookkeeper();
    StepBookkeeper(TrackingSink* sink);

    void UserSteppingAction(const G4Step* step);

  protected:
    TrackingSink* sink;
  private:
    /**/
};

#endif
