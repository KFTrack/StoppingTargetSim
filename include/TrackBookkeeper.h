// Ed Callaghan
// User-level pre-/post-tracking actions
// November 2023

#ifndef TRACKBOOKKEEPER_H
#define TRACKBOOKKEEPER_H

#include <G4Track.hh>
#include <G4UserTrackingAction.hh>
#include <TrackingSink.h>

class TrackBookkeeper: public G4UserTrackingAction{
  public:
    TrackBookkeeper();
   ~TrackBookkeeper();
    TrackBookkeeper(TrackingSink* sink);

    void PreUserTrackingAction(const G4Track* track);
    void PostUserTrackingAction(const G4Track* track);
  protected:
    TrackingSink* sink;
  private:
    /**/
};

#endif
