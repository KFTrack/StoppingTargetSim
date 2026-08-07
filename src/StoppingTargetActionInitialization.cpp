// Ed Callaghan
// User-level action initialization
// October 2023

#include <StoppingTargetActionInitialization.h>

StoppingTargetActionInitialization::StoppingTargetActionInitialization(int run, EventGenerator* generator, std::string opath, std::vector<std::string> kill_volumes, double global_time_limit){
    this->run = run;
    this->generator = generator;
    this->opath = opath;
    this->file.Open(this->opath.c_str(), "RECREATE");
    this->kill_volumes = kill_volumes;
    this->global_time_limit = global_time_limit;
}

StoppingTargetActionInitialization::~StoppingTargetActionInitialization(){
    this->file.Close();
}

void StoppingTargetActionInitialization::Build() const{
    // predefine stepping sink
    auto step_sink = new StepAggregateNtupleTrackingSink(this->run, this->file);

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
    auto track_sink = new NtupleTrackingSink(this->run, this->file);
    auto tbk = new TrackBookkeeper(track_sink);
    this->SetUserAction(tbk);

    // G4UserSteppingAction: end-of-step actions / bookkeeping
    auto msa = new MultiSteppingAction();
    auto sbk = new StepBookkeeper(step_sink);
    auto bvk = new ByVolumeKiller();
    for (const auto& name: this->kill_volumes){
        bvk->AddVolume(name);
    }
    auto btk = new ByGlobalTimeKiller(this->global_time_limit);
    msa->PushAction(sbk);
    msa->PushAction(bvk);
    msa->PushAction(btk);
    this->SetUserAction(msa);
}
