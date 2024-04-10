// Ed Callaghan
// Read particle states from a ROOT TTree
// April 2024

#include <PresampledMuonBeam.h>

PresampledMuonBeam::PresampledMuonBeam(std::string path, std::string key){
    this->file = new TFile(path.c_str());
    this->tree = this->file->Get<TTree>(key.c_str());
    this->entries = this->tree->GetEntries();

    this->fields = NtupleFields();
    this->fields.Register<float>( "x");
    this->fields.Register<float>( "y");
    this->fields.Register<float>( "z");
    this->fields.Register<float>("px");
    this->fields.Register<float>("py");
    this->fields.Register<float>("pz");
    this->fields.Register<int>("pdg");
    this->fields.SetBranchAddresses(this->tree);
}

PresampledMuonBeam::~PresampledMuonBeam(){
    delete this->tree;
    this->file->Close();
}

void PresampledMuonBeam::SampleMuonState(){
    long index = this->sample_entry_number();
    this->tree->GetEntry(index);

    int pdg = this->fields.Get<int>("pdg");
    if (pdg != 13){
        std::string msg = "attempt to generate unsupported particle: pdg "
                        + std::to_string(pdg);
        throw std::runtime_error(msg);
    }

    this->position = G4ThreeVector(this->fields.Get<float>( "x"),
                                   this->fields.Get<float>( "y"),
                                   this->fields.Get<float>( "z"));
    this->momentum = G4ThreeVector(this->fields.Get<float>("px"),
                                   this->fields.Get<float>("py"),
                                   this->fields.Get<float>("pz"));
}

long PresampledMuonBeam::sample_entry_number(){
    double uniform = G4UniformRand();
    long rv = static_cast<long>((this->entries - 1) * uniform);
    return rv;
}
