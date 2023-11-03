// Ed Callaghan
// G4 example main file
// November 2023

#include <StoppingTargetPhysicsList.h>

StoppingTargetPhysicsList::StoppingTargetPhysicsList(){
    /**/
}

StoppingTargetPhysicsList::~StoppingTargetPhysicsList(){
    /**/
}

void StoppingTargetPhysicsList::ConstructParticle(){
    G4BosonConstructor bConstructor;
    bConstructor.ConstructParticle();

    G4LeptonConstructor lConstructor;
    lConstructor.ConstructParticle();

    // others, for when applicable
//  G4MesonConstructor
//  G4BaryonConstructor
//  G4IonConstructor
//  G4ShortlivedConstructor.
}

// TODO
void StoppingTargetPhysicsList::ConstructProcess(){
    auto plh = G4PhysicsListHelper::GetPhysicsListHelper;
    G4ParticleDefinition* particle;

    this->AddTransportation();
}
