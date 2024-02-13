// Ed Callaghan
// ROOT Ntuple-based output of tracking information
// November 2023

#include <NtupleTrackingSink.h>

NtupleTrackingSink::NtupleTrackingSink(std::string path){
    // initialize root classes
    this->file.Open(path.c_str(), "RECREATE");
    this->tree = new TTree("PerTrack", "PerTrack");

    // particle-level metadata
    this->ntuple.Register<Int_t>    ("pdg");
    this->ntuple.Register<Int_t>    ("id");

    // starting information
    this->ntuple.Register<Double_t> ("start_position_x");
    this->ntuple.Register<Double_t> ("start_position_y");
    this->ntuple.Register<Double_t> ("start_position_z");
    this->ntuple.Register<Double_t> ("start_global_time");
    this->ntuple.Register<Double_t> ("start_local_time");
    this->ntuple.Register<Double_t> ("start_momentum_x");
    this->ntuple.Register<Double_t> ("start_momentum_y");
    this->ntuple.Register<Double_t> ("start_momentum_z");
    this->ntuple.Register<Double_t> ("start_kinetic_energy");
    this->ntuple.Register<char*>    ("start_volume");
    this->ntuple.Register<char*>    ("start_process");
    this->ntuple.Register<Double_t> ("start_track_length");
    this->ntuple.Register<Int_t>    ("start_step_number");
    this->ntuple.Register<Bool_t>   ("start_good_for_tracking");

    // ending information
    this->ntuple.Register<Double_t> ("end_position_x");
    this->ntuple.Register<Double_t> ("end_position_y");
    this->ntuple.Register<Double_t> ("end_position_z");
    this->ntuple.Register<Double_t> ("end_global_time");
    this->ntuple.Register<Double_t> ("end_local_time");
    this->ntuple.Register<Double_t> ("end_momentum_x");
    this->ntuple.Register<Double_t> ("end_momentum_y");
    this->ntuple.Register<Double_t> ("end_momentum_z");
    this->ntuple.Register<Double_t> ("end_kinetic_energy");
    this->ntuple.Register<char*>    ("end_volume");
    this->ntuple.Register<char*>    ("end_process");
    this->ntuple.Register<Double_t> ("end_track_length");
    this->ntuple.Register<Int_t>    ("end_step_number");
    this->ntuple.Register<Bool_t>   ("end_good_for_tracking");

    // link to output
    this->ntuple.Branches(tree);
}

NtupleTrackingSink::~NtupleTrackingSink(){
    this->tree->Write("PerTrack", TObject::kOverwrite);
    this->file.Close();
    delete this->tree;
}

void NtupleTrackingSink::PreDigest(const G4Track* track){
    // particle-level metadata
    const G4ParticleDefinition* def = track->GetParticleDefinition();
    this->ntuple.Set("pdg", def->GetPDGEncoding());
    this->ntuple.Set("id", track->GetTrackID());

    // position
    G4ThreeVector pos = track->GetPosition();
    this->ntuple.Set("start_position_x", pos.getX());
    this->ntuple.Set("start_position_y", pos.getY());
    this->ntuple.Set("start_position_z", pos.getZ());

    // momentum
    G4ThreeVector mom = track->GetMomentum();
    this->ntuple.Set("start_momentum_x", mom.getX());
    this->ntuple.Set("start_momentum_y", mom.getY());
    this->ntuple.Set("start_momentum_z", mom.getZ());

    // time
    this->ntuple.Set("start_global_time", track->GetGlobalTime());
    this->ntuple.Set("start_local_time", track->GetGlobalTime());

    // energy
    this->ntuple.Set("start_kinetic_energy", track->GetKineticEnergy());

    // strings
    std::string volume = track->GetVolume()->GetName();
    sprintf(this->start_volume, "%s", volume.c_str());
    this->ntuple.Set("start_volume", this->start_volume);
    const G4VProcess* ptr = track->GetCreatorProcess();
    if (ptr == NULL){
        sprintf(this->start_process, "");
    }
    else{
        const G4String& process = ptr->GetProcessName();
        sprintf(this->start_process, "%s", process.c_str());
    }
    this->ntuple.Set("start_process", this->start_process);

    // miscellany
    this->ntuple.Set("start_track_length", track->GetTrackLength());
    this->ntuple.Set("start_step_number", track->GetCurrentStepNumber());
    this->ntuple.Set("start_good_for_tracking", track->IsGoodForTracking());
}

void NtupleTrackingSink::PostDigest(const G4Track* track){
    // below demonstrates that the value is correctly set...
    // but, for some reason, not correetly written into the root file...
//  auto something = this->ntuple.Get<char*>("start_volume");
//  std::string str(something);

    // position
    G4ThreeVector pos = track->GetPosition();
    this->ntuple.Set("end_position_x", pos.getX());
    this->ntuple.Set("end_position_y", pos.getY());
    this->ntuple.Set("end_position_z", pos.getZ());

    // momentum
    G4ThreeVector mom = track->GetMomentum();
    this->ntuple.Set("end_momentum_x", mom.getX());
    this->ntuple.Set("end_momentum_y", mom.getY());
    this->ntuple.Set("end_momentum_z", mom.getZ());

    // time
    this->ntuple.Set("end_global_time", track->GetGlobalTime());
    this->ntuple.Set("end_local_time", track->GetGlobalTime());

    // energy
    this->ntuple.Set("end_kinetic_energy", track->GetKineticEnergy());

    // strings
    std::string volume = track->GetVolume()->GetName();
    sprintf(this->end_volume, "%s", volume.c_str());
    this->ntuple.Set("end_volume", this->end_volume);
    const G4VProcess* ptr = track->GetCreatorProcess();
    if (ptr == NULL){
        sprintf(this->end_process, "");
    }
    else{
        const G4String& process = ptr->GetProcessName();
        sprintf(this->end_process, "%s", process.c_str());
    }
    this->ntuple.Set("end_process", this->end_process);

    // miscellany
    this->ntuple.Set("end_track_length", track->GetTrackLength());
    this->ntuple.Set("end_step_number", track->GetCurrentStepNumber());
    this->ntuple.Set("end_good_for_tracking", track->IsGoodForTracking());

    // flush to output
    this->tree->Fill();
}
