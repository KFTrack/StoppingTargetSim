// Ed Callaghan
// Factor out some of the ROOT-related bullshit
// December 2022

#include <NtupleField.h>

template <>
void NtupleField<char*>::ConstructType(){
    this->storage = new char [128];
}

template <>
void NtupleField<char*>::DestructType(){
    delete this->storage;
}

template <>
void NtupleField<char*>::Branch(TTree* tree){
    char* addr = &(this->storage[0]);
    tree->Branch(this->GetName().c_str(), addr, this->GetROOTSpec().c_str());
}

template <>
void NtupleField<char*>::Set(char* value){
    sprintf(this->storage, "%s", value);
}
