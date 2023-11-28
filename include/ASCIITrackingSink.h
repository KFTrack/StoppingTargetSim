// Ed Callaghan
// Text-based output of tracking information
// November 2023

#ifndef ASCIITRACKINGSINK_H
#define ASCIITRACKINGSINK_H

#include <iostream>
#include <TrackingSink.h>

class ASCIITrackingSink: public TrackingSink{
  public:
    ASCIITrackingSink(std::ostream& stream);
    void PreDigest(const G4Track* track);
    void PostDigest(const G4Track* track);
    void Digest(const G4Track* track);
  protected:
    std::ostream& stream;
  private:
    /**/
};

#endif
