// Ed Callaghan
// Kill tracks if a step enters forbidden volumes
// April 2026

#include <ByVolumeKiller.h>

ByVolumeKiller::ByVolumeKiller(){
    this->initialized = false;
    this->navigator = G4TransportationManager::GetInstanceIfExist()->GetNavigatorForTracking();
}

ByVolumeKiller::~ByVolumeKiller(){
    /**/
}

void ByVolumeKiller::AddVolume(const std::string volume){
    this->names.push_back(volume);
}

void ByVolumeKiller::UserSteppingAction(const G4Step* step){
    if (!(this->initialized)){
        this->initialize_volume_fields();
    }

    G4Track* track = step->GetTrack();
    const G4ThreeVector position = step->GetPreStepPoint()->GetPosition();

    bool stop = false;
    for (size_t i = 0 ; i < this->volumes.size() && !stop ; i++){
        auto volume = volumes[i];
        if (this->is_contained(position, volume)){
            track->SetTrackStatus(fStopAndKill);
            stop = true;
        }
    }
}

bool ByVolumeKiller::is_contained(const G4ThreeVector& position,
                                   const G4VPhysicalVolume* volume){
    G4VPhysicalVolume* lowest = this->navigator->LocateGlobalPointAndSetup(position, nullptr, false, true);
    G4LogicalVolume* logical = volume->GetLogicalVolume();
    bool rv = ((lowest == volume) || (logical->IsAncestor(lowest)));
    return rv;
}

void ByVolumeKiller::initialize_volume_fields(){
    G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();
    this->volumes.resize(this->names.size());
    for (size_t i = 0 ; i < this->names.size() ; i++){
        auto name = this->names[i];
        this->volumes[i] = store->GetVolume(name);
    }
    this->initialized = true;
}
