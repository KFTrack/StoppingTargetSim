// Ed Callaghan
// Aggregate step-wise metrics into an ntuple
// March 2026

#include <StepAggregateNtupleTrackingSink.h>

StepAggregateNtupleTrackingSink::StepAggregateNtupleTrackingSink(const TFile& file): file(file){
    // initialize root classes
    this->tree = new TTree("PerStepAggregate", "PerStepAggregate");

    // particle-level metadata
    this->ntuple.Register<Int_t>    ("pdg");
    this->ntuple.Register<Int_t>    ("id");

    // key and values
    this->ntuple.Register<char*>    ("volume");
    this->ntuple.Register<Double_t> ("path_length");
    this->ntuple.Register<Double_t> ("energy_loss");

    // link to output
    this->ntuple.Branches(tree);
}

StepAggregateNtupleTrackingSink::~StepAggregateNtupleTrackingSink(){
    this->tree->Write("PerStepAggregate", TObject::kOverwrite);
    delete this->tree;
}

void StepAggregateNtupleTrackingSink::PostDigest(const G4Step* step){
    // reference containing track
    G4Track* track = step->GetTrack();

    // particle-level metadata
    const G4ParticleDefinition* def = track->GetParticleDefinition();
    const auto pdg = def->GetPDGEncoding();
    const auto id = track->GetTrackID();

    // cache metadata
    this->pdgs[id] = pdg;

    // to first order, steps do not cross volume boundaries
    const auto point = step->GetPreStepPoint();
    const auto cstr = point->GetPhysicalVolume()->GetName();
    const std::string volume(cstr);

    if (this->path_length[id].count(volume) < 1){
        this->path_length[id][volume] = 0.0;
        this->energy_loss[id][volume] = 0.0;
    }
    this->path_length[id][volume] += step->GetStepLength();
    this->energy_loss[id][volume] += step->GetDeltaEnergy();
}

void StepAggregateNtupleTrackingSink::Flush(){
    // flush all entries
    for (const auto ppair: this->pdgs){
        // particle-level is duplicatd per entry
        const auto id = ppair.first;
        const auto pdg = this->pdgs[id];
        for (const auto vpair: this->path_length[id]){
            // one row per-particle-per-volume
            const auto volume = vpair.first;
            const auto length = this->path_length[id][volume];
            const auto loss = this->energy_loss[id][volume];
            sprintf(this->volume, "%s", volume.c_str());

            // set all fields
            this->ntuple.Set("id", id);
            this->ntuple.Set("pdg", pdg);
            this->ntuple.Set("volume", this->volume);
            this->ntuple.Set("path_length", length);
            this->ntuple.Set("energy_loss", loss);

            // flush to output
            this->tree->Fill();
        }
    }

    // clear maps for next event
    this->path_length.clear();
    this->energy_loss.clear();
}
