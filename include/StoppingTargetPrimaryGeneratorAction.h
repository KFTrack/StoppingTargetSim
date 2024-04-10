// Ed Callaghan
// User-level primary generator action
// October 2023

#ifndef STOPPINGTARGETPRIMARYGENERATORACTION_H
#define STOPPINGTARGETPRIMARYGENERATORACTION_H

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleGun.hh>

#include <EventGenerator.h>

class StoppingTargetPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{
  public:
    StoppingTargetPrimaryGeneratorAction(EventGenerator* generator);
   ~StoppingTargetPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);
  protected:
    EventGenerator* generator;
  private:
  	/**/
};

#endif
