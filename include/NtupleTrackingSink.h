// Ed Callaghan
// ROOT Ntuple-based output of tracking information
// November 2023

#ifndef TNTUPLETRACKINGSINK_H
#define TNTUPLETRACKINGSINK_H

#include <TFile.h>
#include <TTree.h>
#include <NtupleFields.h>
#include <TrackingSink.h>
#include <string>

class NtupleTrackingSink: public TrackingSink{
  public:
    NtupleTrackingSink(std::string path);
   ~NtupleTrackingSink();
    void PreDigest(const G4Track* track);
    void PostDigest(const G4Track* track);
  protected:
    TFile file;
    TTree* tree;
    NtupleFields ntuple;
  private:
    /**/
};

#endif

