// Ed Callaghan
// User-level primary generator action
// October 2023

#include <StoppingTargetPrimaryGeneratorAction.h>

StoppingTargetPrimaryGeneratorAction::StoppingTargetPrimaryGeneratorAction(EventGenerator* generator){
    this->generator = generator;
}

StoppingTargetPrimaryGeneratorAction::~StoppingTargetPrimaryGeneratorAction(){
}

// TODO eventually, this will update the gun before each shot
void StoppingTargetPrimaryGeneratorAction::GeneratePrimaries(G4Event* event){
    this->generator->GeneratePrimaries(event);
}
