// Ed Callaghan
// ROOT Ntuple-based output of tracking information
// November 2023

#ifndef TNTUPLETRACKINGSINK_H
#define TNTUPLETRACKINGSINK_H

#include <string>
#include <TFile.h>
#include <TTree.h>
#include <G4VProcess.hh>
#include <NtupleFields.h>
#include <TrackingSink.h>

class NtupleTrackingSink: public TrackingSink{
  public:
    NtupleTrackingSink(std::string path);
   ~NtupleTrackingSink();
    void PreDigest(const G4Track* track);
    void PostDigest(const G4Track* track);
  protected:
    TFile file;
    TTree* tree;

    // home-rolled interface to TTree management
    NtupleFields ntuple;
    char start_volume[128];
    char start_process[128];
    char end_volume[128];
    char end_process[128];

  private:
    /**/
};

#endif
