// Ed Callaghan
// End-point interface for tracking information
// November 2023

#ifndef TRACKINGSINK_H
#define TRACKINGSINK_H

#include <G4Step.hh>
#include <G4Track.hh>

class TrackingSink{
  public:
    TrackingSink();
    virtual ~TrackingSink();
    virtual void PreDigest(const G4Track*);
    virtual void PostDigest(const G4Track*);
    virtual void PreDigest(const G4Step*);
    virtual void PostDigest(const G4Step*);
  protected:
    /**/
  private:
    /**/
};

#endif
