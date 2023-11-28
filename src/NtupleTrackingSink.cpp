// Ed Callaghan
// ROOT Ntuple-based output of tracking information
// November 2023

#include <NtupleTrackingSink.h>

NtupleTrackingSink::NtupleTrackingSink(std::string path){
    // initialize root classes
    this->file.Open(path.c_str(), "RECREATE");
    this->tree = new TTree("PerTrack", "PerTrack");

    // starting information
    this->ntuple.Register<Double_t> ("start_position_x");
    this->ntuple.Register<Double_t> ("start_position_y");
    this->ntuple.Register<Double_t> ("start_position_z");
    this->ntuple.Register<Double_t> ("start_momentum_x");
    this->ntuple.Register<Double_t> ("start_momentum_y");
    this->ntuple.Register<Double_t> ("start_momentum_z");

    // ending information
    this->ntuple.Register<Double_t> ("end_position_x");
    this->ntuple.Register<Double_t> ("end_position_y");
    this->ntuple.Register<Double_t> ("end_position_z");
    this->ntuple.Register<Double_t> ("end_momentum_x");
    this->ntuple.Register<Double_t> ("end_momentum_y");
    this->ntuple.Register<Double_t> ("end_momentum_z");

    // link to output
    this->ntuple.Branches(tree);
}

NtupleTrackingSink::~NtupleTrackingSink(){
    this->tree->Write();
    this->file.Close();
    delete this->tree;
}

void NtupleTrackingSink::PreDigest(const G4Track* track){
    G4ThreeVector pos = track->GetPosition();
    this->ntuple.Set("start_position_x", pos.getX());
    this->ntuple.Set("start_position_y", pos.getY());
    this->ntuple.Set("start_position_z", pos.getZ());

    G4ThreeVector mom = track->GetMomentum();
    this->ntuple.Set("start_position_x", mom.getX());
    this->ntuple.Set("start_position_y", mom.getY());
    this->ntuple.Set("start_position_z", mom.getZ());
}

void NtupleTrackingSink::PostDigest(const G4Track* track){
    G4ThreeVector pos = track->GetPosition();
    this->ntuple.Set("end_position_x", pos.getX());
    this->ntuple.Set("end_position_y", pos.getY());
    this->ntuple.Set("end_position_z", pos.getZ());

    G4ThreeVector mom = track->GetMomentum();
    this->ntuple.Set("end_position_x", mom.getX());
    this->ntuple.Set("end_position_y", mom.getY());
    this->ntuple.Set("end_position_z", mom.getZ());

    // flush to output
    this->tree->Fill();
}
