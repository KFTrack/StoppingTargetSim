// Ed Callaghan
// Aggregate step-wise metrics into an ntuple
// March 2026

#ifndef STEPAGGREGATENTUPLETRACKINGSINK_H
#define STEPAGGREGATENTUPLETRACKINGSINK_H

#include <map>
#include <TFile.h>
#include <TTree.h>
#include <G4VProcess.hh>
#include <NtupleFields.h>
#include <TrackingSink.h>

class StepAggregateNtupleTrackingSink: public TrackingSink{
  public:
    StepAggregateNtupleTrackingSink(const TFile& file);
   ~StepAggregateNtupleTrackingSink();
    void PostDigest(const G4Step* step);
    void Flush();

  protected:
    const TFile& file;
    TTree* tree;

    // home-rolled interface to TTree management
    NtupleFields ntuple;
    char volume[128];

    // nested mapping of volume name to track aggregates
    using VolumeMap = std::map<std::string, double>;
    using PID_t = Int_t;
    using PDG_t = Int_t;
    using ParticleMap = std::map<PID_t, VolumeMap>;
    std::map<PID_t, PDG_t> pdgs;
    ParticleMap path_length;
    ParticleMap energy_loss;

  private:
    /**/
};

#endif
