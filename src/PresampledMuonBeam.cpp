// Ed Callaghan
// Read particle states from a ROOT TTree
// April 2024

#include <PresampledMuonBeam.h>

PresampledMuonBeam::PresampledMuonBeam(std::string path, std::string key,
                                       float ox, float oy, float oz,
                                       unsigned int volume_index):
                                           origin(ox, oy, oz),
                                           volume_index(volume_index){
    this->file = new TFile(path.c_str());
    this->tree = this->file->Get<TTree>(key.c_str());
    this->entries = this->tree->GetEntries();

    this->fields = NtupleFields();
    this->fields.Register<float>( "ex");
    this->fields.Register<float>( "ey");
    this->fields.Register<float>( "ez");
    this->fields.Register<float>("epx");
    this->fields.Register<float>("epy");
    this->fields.Register<float>("epz");
    this->fields.Register<float>("pdg");
    this->fields.Register<float>("evid");
    this->fields.SetBranchAddresses(this->tree);
}

PresampledMuonBeam::~PresampledMuonBeam(){
    delete this->tree;
    this->file->Close();
}

void PresampledMuonBeam::SampleMuonState(){
    unsigned int volume_index;
    do{
        // sample until we encounter a muon
        long index;
        int pdg;
        do {
            index = this->sample_entry_number();
            this->tree->GetEntry(index);
            float fpdg = this->fields.Get<float>("pdg");
            pdg = static_cast<int>(fpdg);
        } while (pdg != 13);

        // which is in the correct volume
        float fevid = this->fields.Get<float>("evid");
        volume_index = static_cast<unsigned int>(fevid);
    } while (volume_index != this->volume_index);

    this->position = G4ThreeVector(this->fields.Get<float>( "ex"),
                                   this->fields.Get<float>( "ey"),
                                   this->fields.Get<float>( "ez"));
    this->momentum = G4ThreeVector(this->fields.Get<float>("epx"),
                                   this->fields.Get<float>("epy"),
                                   this->fields.Get<float>("epz"));
    this->position += this->origin;
}

long PresampledMuonBeam::sample_entry_number(){
    double uniform = G4UniformRand();
    long rv = static_cast<long>((this->entries - 1) * uniform);
    return rv;
}
