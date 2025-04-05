// Ed Callaghan
// Monoenergetic electrons sampled spatially from within a G4 volume
// October 2024

#include <MonoenergeticElectronsInVolume.h>

MonoenergeticElectronsInVolume::MonoenergeticElectronsInVolume(double energy,
                                                         std::string name){
    // generic setup
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* def = particleTable->FindParticle("e-");

    this->gun = new G4ParticleGun(1);
    this->gun->SetParticleDefinition(def);

    // defer initialization of G4-coupled fields to runtime
    this->volume_name = name;
    this->initialized = false;

    // kinematic book-keeping
    double mass = def->GetPDGMass();
    this->energy = energy;
    this->momentum_magnitude = pow(pow(this->energy, 2) - pow(mass, 2), 0.5);
}

MonoenergeticElectronsInVolume::~MonoenergeticElectronsInVolume(){
  /**/
}

void MonoenergeticElectronsInVolume::SampleElectronState(){
    // first, initialize G4Volume info, if necessary...
    if (!initialized){
        this->initialize_volume_fields();
    }

    // next, sample the position... i.e.
    // sample points in the volume's bounding box until one is chosen
    // inside of the actual volume
    bool stop = false;
    while (!stop){
        double ux = G4UniformRand();
        double uy = G4UniformRand();
        double uz = G4UniformRand();
        double x = this->xmin + ux * (this->xmax - this->xmin);
        double y = this->ymin + uy * (this->ymax - this->ymin);
        double z = this->zmin + uz * (this->zmax - this->zmin);
        G4ThreeVector candidate(x, y, z);
        this->global.ApplyPointTransform(candidate);
        G4VPhysicalVolume* lowest = this->navigator->LocateGlobalPointAndSetup(candidate, nullptr, false, true);
        G4LogicalVolume* logical = this->volume->GetLogicalVolume();
        if ((lowest == this->volume) || (logical->IsAncestor(lowest))){
            this->position = candidate;
            stop = true;
        }
    }

    // finally, sample the direction...
    double polar = acos(2.0 * G4UniformRand() - 1.0);
    double azimuth = CLHEP::twopi * G4UniformRand();
    double dx = sin(polar) * cos(azimuth);
    double dy = sin(polar) * sin(azimuth);
    double dz = cos(polar);
    G4ThreeVector direction(dx, dy, dz);
    this->momentum = this->momentum_magnitude * direction;
}

void MonoenergeticElectronsInVolume::GeneratePrimaries(G4Event* event){
    this->SampleElectronState();
    this->gun->SetParticlePosition(this->position);
    this->gun->SetParticleMomentum(this->momentum);
    this->gun->GeneratePrimaryVertex(event);
}

void MonoenergeticElectronsInVolume::initialize_volume_fields(){
    G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();
    this->volume = store->GetVolume(this->volume_name);
    G4VSolid* solid = this->volume->GetLogicalVolume()->GetSolid();

    G4VoxelLimits limits;
    G4AffineTransform transform;
    solid->CalculateExtent(kXAxis, limits, transform, this->xmin, this->xmax);
    solid->CalculateExtent(kYAxis, limits, transform, this->ymin, this->ymax);
    solid->CalculateExtent(kZAxis, limits, transform, this->zmin, this->zmax);

    // build translation from local to global coordinates
    // by successively transforming from one volumes coordinates
    // into its direct mother's, until the top-level world
    this->global = transform;
    G4VPhysicalVolume* world = store->GetVolume("world");
    G4VPhysicalVolume* current = this->volume;
    while (current != world){
        // TODO GetFrame* or GetObject*
        auto rotation = current->GetObjectRotation();
        auto translation = current->GetObjectTranslation();
        G4AffineTransform tmp(rotation, translation);
        this->global *= tmp;
        current = store->GetVolume(current->GetMotherLogical()->GetName());
    }

    this->navigator = G4TransportationManager::GetInstanceIfExist()->GetNavigatorForTracking();

    this->initialized = true;
}
