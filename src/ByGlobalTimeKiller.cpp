// Ed Callaghan
// Kill tracks after a certain global time has elapsed
// April 2026

#include <ByGlobalTimeKiller.h>

ByGlobalTimeKiller::ByGlobalTimeKiller(double limit){
    this->limit = limit;
}

ByGlobalTimeKiller::~ByGlobalTimeKiller(){
    /**/
}

void ByGlobalTimeKiller::UserSteppingAction(const G4Step* step){
    if (this->limit < step->GetPostStepPoint()->GetGlobalTime()){
        G4Track* track = step->GetTrack();
        track->SetTrackStatus(fStopAndKill);
    }
}
