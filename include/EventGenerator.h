// Ed Callaghan
// Base class for generate G4 events
// April 2024

#ifndef EVENTGENERATOR_HH
#define EVENTGENERATOR_HH

#include <G4Event.hh>

class EventGenerator{
  public:
    EventGenerator(){};
   ~EventGenerator(){};

    virtual void GeneratePrimaries(G4Event*) = 0;
  private:
    /**/
  protected:
    /**/
};

#endif
