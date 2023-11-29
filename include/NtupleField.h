// Ed Callaghan
// Factor out some of the ROOT-related bullshit
// December 2022; November 2023

#ifndef NTUPLEFIELD_H
#define NTUPLEFIELD_H

#include <map>
#include <string>
#include <TypeLabels.h>

template <typename T>
class NtupleField{
  public:
    NtupleField();
    NtupleField(std::string name);
   ~NtupleField();
    std::string GetName();
    std::string GetType();
    std::string GetCode();
    std::string GetROOTSpec();
    T* GetStorageAddress();
    void Set(const T value);
  protected:
    std::string name;
    std::string type;
    T storage;
  private:
    /**/
};

template <typename T>
NtupleField<T>::NtupleField(){
    /* */
}

template <typename T>
NtupleField<T>::NtupleField(std::string name){
    this->name = name;
    this->type = GetTypeLabel<T>();
}

template <typename T>
NtupleField<T>::~NtupleField(){
    /* */
}

template <typename T>
std::string NtupleField<T>::GetName(){
    std::string rv = this->name;
    return rv;
}

template<typename T>
std::string NtupleField<T>::GetType(){
    std::string rv = this->type;
    return rv;
}

template <typename T>
std::string NtupleField<T>::GetCode(){
    std::string rv = GetTypeCode(this->GetType());
    return rv;
}

template <typename T>
std::string NtupleField<T>::GetROOTSpec(){
    std::string rv = this->GetName() + "/" + this->GetCode();
    return rv;
}

template <typename T>
T* NtupleField<T>::GetStorageAddress(){
    T* rv = &(this->storage);
    return rv;
}

template <typename T>
void NtupleField<T>::Set(T value){
    this->storage = value;
}

#endif
