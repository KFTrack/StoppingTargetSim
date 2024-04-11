// Ed Callaghan
// Read particle states from a ROOT TTree
// April 2024

#ifndef PRESAMPLEDGENERATOR_H
#define PRESAMPLEDGENERATOR_H

#include <string>
#include <stdexcept>
#include <TFile.h>
#include <TTree.h>
#include <Randomize.hh>
#include <NtupleFields.h>
#include <MuonBeam.h>

class PresampledMuonBeam: public MuonBeam{
  public:
    PresampledMuonBeam(std::string path, std::string key);
   ~PresampledMuonBeam();

    virtual void SampleMuonState();
  protected:
    TFile* file;
    TTree* tree;
    NtupleFields fields;

    long entries;
    long sample_entry_number();
  private:
    /**/
};

#endif
