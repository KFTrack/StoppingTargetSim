// Ed Callaghan
// Container class to allow iterating over types in a sane (?) way
// December 2022; November 2023

#ifndef NTUPLEFIELDS_H__
#define NTUPLEFIELDS_H__

#include <map>
#include <string>
#include <vector>
#include <TTree.h>
#include <NtupleField.h>
#include <TypeLabels.h>

class NtupleFields{
  public:
    NtupleFields();
   ~NtupleFields();

    template<typename T>
    void Register(std::string name);
    template<typename T>
    std::vector< NtupleField<T>* > GetFields();

    template<typename T>
    void SetBranchAddressesTyped(TTree* tree);
    void SetBranchAddresses(TTree* tree);

    template<typename T>
    void BranchesTyped(TTree* tree);
    void Branches(TTree* tree);

    template<typename T>
    void Set(std::string name, T value);

  protected:
    std::map< std::string, std::vector<void*> > vectors;
    std::map< std::string, std::map< std::string, void* > > maps;

    template<typename T>
    void initialize();

  private:
    /**/
};

template<typename T>
void NtupleFields::initialize(){
    std::string label = GetTypeLabel<T>();
    this->vectors[label] = std::vector< void* >();
    this->maps[label] = std::map<std::string, void* >();
}

template<typename T>
void NtupleFields::Register(std::string name){
    std::string type = GetTypeLabel<T>();
    NtupleField<T>* field = new NtupleField<T>(name);
    this->vectors[type].push_back((void*) field);
    this->maps[type][name] = (void*) field;
}

template<typename T>
std::vector< NtupleField<T>* > NtupleFields::GetFields(){
    std::string type = GetTypeLabel<T>();
    std::vector< void* >& stored = this->vectors[type];
    std::vector< NtupleField<T>* > rv(stored.size());
    for (int i = 0 ; i < rv.size() ; i++){
        rv[i] = (NtupleField<T>*) stored[i];
    }
    return rv;
}

template<typename T>
void NtupleFields::SetBranchAddressesTyped(TTree* tree){
    std::vector< NtupleField<T>* > fields = this->GetFields<T>();
    for (int i = 0 ; i < fields.size() ; i++){
        NtupleField<T>* field = fields[i];
        T* addr = field->GetStorageAddress();
        tree->SetBranchAddress(field->GetName().c_str(), addr);
    }
}

template<typename T>
void NtupleFields::BranchesTyped(TTree* tree){
    std::vector< NtupleField<T>* > fields = this->GetFields<T>();
    for (int i = 0 ; i < fields.size() ; i++){
        NtupleField<T>* field = fields[i];
        T* addr = field->GetStorageAddress();
        tree->Branch(field->GetName().c_str(), addr, field->GetROOTSpec().c_str());
    }
}

template<typename T>
void NtupleFields::Set(std::string name, T value){
    std::string type = GetTypeLabel<T>();
    std::map< std::string, void* >& stored = this->maps[type];
    NtupleField<T>* field = (NtupleField<T>*) stored[name];
    field->Set(value);
}

#endif
