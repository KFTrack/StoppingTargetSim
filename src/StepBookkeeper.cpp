// Ed Callaghan
// User-level stepping actions
// March 2026

#include <StepBookkeeper.h>

StepBookkeeper::StepBookkeeper(){
    /**/
}

StepBookkeeper::~StepBookkeeper(){
    delete this->sink;
}

StepBookkeeper::StepBookkeeper(TrackingSink* sink){
    this->sink = sink;
}

void StepBookkeeper::UserSteppingAction(const G4Step* step){
    this->sink->PostDigest(step);
}
