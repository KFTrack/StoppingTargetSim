// Ed Callaghan
// Maintain sequence of individual stepping actions
// April 2026

#include <MultiSteppingAction.h>

MultiSteppingAction::MultiSteppingAction(){
    /**/
}

MultiSteppingAction::~MultiSteppingAction(){
    for (size_t i = 0 ; i < this->actions.size() ; i++){
        delete this->actions[i];
    }
}

void MultiSteppingAction::PushAction(G4UserSteppingAction* action){
    this->actions.push_back(action);
}

void MultiSteppingAction::UserSteppingAction(const G4Step* step){
    for (size_t i = 0 ; i < this->actions.size() ; i++){
        this->actions[i]->UserSteppingAction(step);
    }
}
