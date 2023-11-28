// Ed Callaghan
// User-level pre-/post-tracking actions
// November 2023

#include <TrackBookkeeper.h>

TrackBookkeeper::TrackBookkeeper(){
    /**/
}

TrackBookkeeper::~TrackBookkeeper(){
    delete this->sink;
}

TrackBookkeeper::TrackBookkeeper(TrackingSink* sink){
    this->sink = sink;
}

void TrackBookkeeper::PreUserTrackingAction(const G4Track* track){
    this->sink->PreDigest(track);
}

void TrackBookkeeper::PostUserTrackingAction(const G4Track* track){
    this->sink->PostDigest(track);
}
