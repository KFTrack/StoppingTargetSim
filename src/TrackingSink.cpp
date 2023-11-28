// Ed Callaghan
// End-point interface for tracking information
// November 2023

#include <TrackingSink.h>

TrackingSink::TrackingSink(){
    /**/
}

TrackingSink::~TrackingSink(){
    /**/
}

// by default, absorb tracks into the abyss
void TrackingSink::PreDigest(const G4Track*){
    /**/
}

// by default, absorb tracks into the abyss
void TrackingSink::PostDigest(const G4Track*){
    /**/
}

// by default, absorb steps into the abyss
void TrackingSink::PreDigest(const G4Step*){
    /**/
}

// by default, absorb steps into the abyss
void TrackingSink::PostDigest(const G4Step*){
    /**/
}
