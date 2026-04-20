// Ed Callaghan
// Kill tracks after a certain global time has elapsed
// April 2026

#ifndef BYGLOBALTIMEKILLER_H
#define BYGLOBALTIMEKILLER_H

#include <G4Track.hh>
#include <G4TrackStatus.hh>
#include <G4UserSteppingAction.hh>

class ByGlobalTimeKiller: public G4UserSteppingAction{
  public:
    ByGlobalTimeKiller(double limit);
   ~ByGlobalTimeKiller();

    void UserSteppingAction(const G4Step* step);

  protected:
    double limit;

  private:
    /**/
};

#endif
