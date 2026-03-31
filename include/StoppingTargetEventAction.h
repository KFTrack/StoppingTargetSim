// Ed Callaghan
// End-of-event callback, primarily to flush aggregate ntuples to disk
// March 2026

#include <G4Event.hh>
#include <G4UserEventAction.hh>
#include <StepAggregateNtupleTrackingSink.h>

class StoppingTargetEventAction: public G4UserEventAction{
  public:
    StoppingTargetEventAction(StepAggregateNtupleTrackingSink*);
    void EndOfEventAction(const G4Event*);

  protected:
    StepAggregateNtupleTrackingSink* sink;

  private:
    /**/
};
