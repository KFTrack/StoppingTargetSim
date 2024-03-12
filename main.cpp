// Ed Callaghan
// G4 example main file
// October 2023

// systemwide
#include <unistd.h>
#include <iostream>
#include <string>

// yaml parser
#include <YamlParser.h>
#include <c4/charconv.hpp>

// ROOT includes
//#include <TROOT.h>
#include <TApplication.h>

// G4 includes
#include <G4PhysListFactory.hh>
#include <G4RunManagerFactory.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <Randomize.hh>

// customization for Stopping Target studies
#include <StoppingTargetActionInitialization.h>
#include <StoppingTargetDetectorConstruction.h>
//#include <StoppingTargetPhysicsList.h>

using namespace std;

int main(int argc, char** argv){
    int c;
    string ipath;
    string opath;
    bool vis = false;
    bool shell = false;
    long seed = 1; // TODO hash of PID and system time
    while ((c = getopt(argc, argv, "i:o:s:vx")) != -1){
        switch(c){
            // path to macro
            case 'i':
                ipath = string(optarg);
                break;
            // path to output
            case 'o':
                opath = string(optarg);
                break;
            // random seed
            case 's':
                seed = atol(optarg);
                break;
            // optional visualization
            case 'v':
                vis = true;
                break;
            // optionally drop into G4 shell
            case 'x':
                shell = true;
                break;
            default:
                cerr << "error: unexpected option"
                     << endl;
                exit(1);
        }
    }

    if (ipath.size() == 0){
        cerr << "error: must specify path to configuration (-i)"
             << endl;
        exit(1);
    }
    if (opath.size() == 0){
        opath = ipath + "-out.root";
        cerr << "warning: no output specified (-o), defaulting to "
             << opath
             << endl;
    }

    YamlParser parser;
    YamlNode config = parser.Parse(ipath);

    // random seed
    CLHEP::HepRandom::setTheSeed(seed);

//  will likely be necessary for multi-threaded G4, but we aren't there yet
//  ROOT::EnableThreadSafety();
    TApplication app("TApplication", 0, NULL);

    // instantiate run manager
    // TODO details of initializations and geometries from config
    auto manager = G4RunManagerFactory::CreateRunManager();
//  manager->SetUserInitialization(new StoppingTargetPhysicsList);
    auto plf = G4PhysListFactory();
    auto list = plf.GetReferencePhysList("FTFP_BERT");
    manager->SetUserInitialization(list);
    auto stai = new StoppingTargetActionInitialization(opath);
    manager->SetUserInitialization(stai);
    auto stdc = new StoppingTargetDetectorConstruction();
    manager->SetUserInitialization(stdc);

    manager->Initialize();

    // run simulation
    unsigned int events = config["events"].Value<unsigned int>();
    manager->BeamOn(events);

    // invoke G4 commands to enact visualization
    G4VisExecutive* visMgr = NULL;
    if (vis){
        visMgr = new G4VisExecutive();
        visMgr->Initialize();
    }

    // execute generic G4 commands; really, this should only be used for
    // visualization or playing around
    if (config.has_child("macro")){
        G4UImanager* ui = G4UImanager::GetUIpointer();
        auto commands = config["macro"];
        // TODO iteration over sequence returns ryml::ConstNodeRef, but
        // being able to directly iterate over YamlNodes would be nice
        for (auto command : commands){
            ui->ApplyCommand(YamlNode(command).Value<string>());
        }
    }

    // drop into G4 shell, useful for playing around
    if (shell){
        G4UIExecutive* executive = new G4UIExecutive(argc, argv);
        executive->SessionStart();
    }

    // clean up
    delete manager;

    return 0;
}
