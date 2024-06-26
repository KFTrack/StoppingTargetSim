// Ed Callaghan
// User-level action initialization
// October 2023

#include <StoppingTargetActionInitialization.h>

StoppingTargetActionInitialization::StoppingTargetActionInitialization(EventGenerator* generator, std::string opath){
    this->generator = generator;
    this->opath = opath;
}

StoppingTargetActionInitialization::~StoppingTargetActionInitialization(){
    /**/
}

void StoppingTargetActionInitialization::Build() const{
    // call below, as applicable

    // G4VUserPrimaryGeneratorAction: specify primary particles
    // this->SetUserAction(G4VUserPrimaryGeneratorAction*);
    auto generatorAction =
        new StoppingTargetPrimaryGeneratorAction(this->generator);
    this->SetUserAction(generatorAction);

    // G4UserRunAction: begin-/end-of-run bookkeeping
    // this->SetUserAction(G4UserRunAction*);

    // G4UserEventAction: begin-/end-of-event bookkeeping
    // this->SetUserAction(G4UserEventAction*);

    // G4UserStackingAction: details of track stacking
    // this->SetUserAction(G4UserStackingAction*);

    // G4UserTrackingAction: begin-/end-of-track actions / bookkeeping
    // this->SetUserAction(G4UserTrackingAction*);
    auto sink = new NtupleTrackingSink(this->opath);
    auto tbk = new TrackBookkeeper(sink);
    this->SetUserAction(tbk);

    // G4UserSteppingAction: end-of-step actions / bookkeeping
    // this->SetUserAction(G4UserSteppingAction*);
}
