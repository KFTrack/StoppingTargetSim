// Ed Callaghan
// Text-based output of tracking information
// November 2023

#include <ASCIITrackingSink.h>

ASCIITrackingSink::ASCIITrackingSink(std::ostream& _stream): stream(_stream){
    /**/
}

void ASCIITrackingSink::PreDigest(const G4Track* track){
    this->stream << "Pre:" << std::endl;
    this->Digest(track);
}

void ASCIITrackingSink::PostDigest(const G4Track* track){
    this->stream << "Post:" << std::endl;
    this->Digest(track);
}

void ASCIITrackingSink::Digest(const G4Track* track){
    const G4ThreeVector pos = track->GetPosition();
    const G4ThreeVector mom = track->GetMomentum();
    this->stream << pos.getX() << ' ' 
                 << pos.getY() << ' '
                 << pos.getZ() << ' '
                 << mom.getX() << ' ' 
                 << mom.getY() << ' '
                 << mom.getZ() << ' '
                 << std::endl;
}
