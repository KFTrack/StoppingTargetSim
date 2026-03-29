// Ed Callaghan
// User-level action initialization
// October 2023

#include <StoppingTargetActionInitialization.h>

StoppingTargetActionInitialization::StoppingTargetActionInitialization(EventGenerator* generator, std::string opath){
    this->generator = generator;
    this->opath = opath;
    this->file.Open(this->opath.c_str(), "RECREATE");
}

StoppingTargetActionInitialization::~StoppingTargetActionInitialization(){
    this->file.Close();
}

void StoppingTargetActionInitialization::Build() const{
    // predefine stepping sink
    auto step_sink = new StepAggregateNtupleTrackingSink(this->file);

    // call below, as applicable

    // G4VUserPrimaryGeneratorAction: specify primary particles
    // this->SetUserAction(G4VUserPrimaryGeneratorAction*);
    auto generatorAction =
        new StoppingTargetPrimaryGeneratorAction(this->generator);
    this->SetUserAction(generatorAction);

    // G4UserRunAction: begin-/end-of-run bookkeeping
    // this->SetUserAction(G4UserRunAction*);

    // G4UserEventAction: begin-/end-of-event bookkeeping
    auto eventAction = new StoppingTargetEventAction(step_sink);
    this->SetUserAction(eventAction);

    // G4UserStackingAction: details of track stacking
    // this->SetUserAction(G4UserStackingAction*);

    // G4UserTrackingAction: begin-/end-of-track actions / bookkeeping
    // this->SetUserAction(G4UserTrackingAction*);
    auto track_sink = new NtupleTrackingSink(this->file);
    auto tbk = new TrackBookkeeper(track_sink);
    this->SetUserAction(tbk);

    // G4UserSteppingAction: end-of-step actions / bookkeeping
    auto sbk = new StepBookkeeper(step_sink);
    this->SetUserAction(sbk);
}
