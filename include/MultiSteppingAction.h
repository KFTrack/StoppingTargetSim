// Ed Callaghan
// Maintain sequence of individual stepping actions
// April 2026

#ifndef MULTISTEPPINGACTION_H
#define MULTISTEPPINGACTION_H

#include <vector>
#include <G4UserSteppingAction.hh>

class MultiSteppingAction: public G4UserSteppingAction{
  public:
    MultiSteppingAction();
   ~MultiSteppingAction();

   void PushAction(G4UserSteppingAction* action);
   void UserSteppingAction(const G4Step* step);

  protected:
    std::vector<G4UserSteppingAction*> actions;

  private:
    /**/
};

#endif
