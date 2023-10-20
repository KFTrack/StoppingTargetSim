// Ed Callaghan
// G4 example main file
// October 2023

// G4 includes
#include <G4RunManagerFactory.hh>
#include <G4UImanager.hh>

#include <StoppingTargetActionInitialization.h>
//#include <StoppingTargetDetectorConstruction.h>
//#include <StoppingTargetPhysicsList.h>

int main(int argc, char** argv){
    // instantiate run manager
    auto manager = G4RunManagerFactory::CreateRunManager();
//  manager->SetUserInitialization(new StoppingTargetDetectorConstruction);
//  manager->SetUserInitialization(new StoppingTargetPhysicsList);
//  manager->SetUserInitialization(new StoppingTargetActionInitialization);
//  manager->Initialize();

    return 0;
}
