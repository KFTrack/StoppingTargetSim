// Ed Callaghan
// G4 example main file
// October 2023

// systemwide
#include <unistd.h>
#include <iostream>
#include <string>

// G4 includes
#include <G4RunManagerFactory.hh>
#include <G4UImanager.hh>

// customization for Stopping Target studies
#include <StoppingTargetActionInitialization.h>
//#include <StoppingTargetDetectorConstruction.h>
#include <StoppingTargetPhysicsList.h>

using namespace std;

int main(int argc, char** argv){
    int c;
    string ipath;
    string opath;
    while ((c = getopt(argc, argv, "i:o:")) != -1){
        switch(c){
            // path to macro
            case 'i':
                ipath = string(optarg);
                break;
            // path to output
            case 'o':
                opath = string(optarg);
                break;
            default:
                cerr << "error: unexpected option"
                     << endl;
                exit(1);
        }
    }

    if (ipath.size() == 0){
        cerr << "error: must specify path to macro (-i)"
             << endl;
        exit(1);
    }
    if (opath.size() == 0){
        opath = ipath + "-out.root";
        cerr << "warning: no output specified (-o), defaulting to "
             << opath
             << endl;
    }

    // instantiate run manager
    auto manager = G4RunManagerFactory::CreateRunManager();
    manager->SetUserInitialization(new StoppingTargetActionInitialization);
//  manager->SetUserInitialization(new StoppingTargetDetectorConstruction);
    manager->SetUserInitialization(new StoppingTargetPhysicsList);
//  manager->Initialize();

    return 0;
}
