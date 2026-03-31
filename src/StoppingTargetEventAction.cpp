// Ed Callaghan
// End-of-event callback, primarily to flush aggregate ntuples to disk
// March 2026

#include <StoppingTargetEventAction.h>

StoppingTargetEventAction::StoppingTargetEventAction(StepAggregateNtupleTrackingSink* sink){
    this->sink = sink;
}

void StoppingTargetEventAction::EndOfEventAction(const G4Event* event){
    this->sink->Flush();
}

