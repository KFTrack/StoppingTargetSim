// Ed Callaghan
// Monoenergetic electrons sampled spatially from within multiple G4 volumes
// April 2025

#include <MonoenergeticElectronsInVolumes.h>

MonoenergeticElectronsInVolumes::MonoenergeticElectronsInVolumes(double energy,
                                                std::vector<std::string> names){
  this->initialized = false;
  this->volume_names = names;
  for (const auto& name: this->volume_names){
    this->generators.emplace_back(energy, name);
  }
}

MonoenergeticElectronsInVolumes::~MonoenergeticElectronsInVolumes(){
  /**/
}

void MonoenergeticElectronsInVolumes::GeneratePrimaries(G4Event* event){
  // initialize weights, if necessary
  if (!this->initialized){
    this->initialize_weights();
  }

  // sample uniform and translate to a chosen volume
  double u = G4UniformRand();
  size_t idx = 0;
  while (this->cumulative_weights[idx] < u){
    idx++;
  }

  // defer workload to generator for that volume
  auto& generator = this->generators[idx];
  generator.GeneratePrimaries(event);
}

void MonoenergeticElectronsInVolumes::initialize_weights(){
    // first, cache each volume's mass
    G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();
    double total = 0.0;
    for (const auto& name: this->volume_names){
      const auto& volume = store->GetVolume(name);
      const auto& logical = volume->GetLogicalVolume();
      double mass = logical->GetMass();
      this->weights.push_back(mass);
      total += mass;
    }

    // then, normalize so that the weights sum to 1.0
    for (size_t i = 0 ; i < this->weights.size() ; i++){
      this->weights[i] /= total;
    }

    // finally, cache cumulative weights to enable uniform-to-generator lookup
    this->cumulative_weights.resize(this->weights.size());
    this->cumulative_weights[0] = this->weights[0];
    for (size_t i = 1 ; i < this->weights.size() ; i++){
      double running = this->cumulative_weights[i-1];
      double current = this->weights[i];
      this->cumulative_weights[i] = running + current;
    }

    // mark as done
    this->initialized = true;
}
