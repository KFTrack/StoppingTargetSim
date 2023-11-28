// Ed Callaghan
// Container class to allow iterating over types in a sane (?) way
// December 2022

#include <NtupleFields.h>

NtupleFields::NtupleFields(){
    this->initialize<char*>     ();
    this->initialize<Char_t>    ();
    this->initialize<UChar_t>   ();
    this->initialize<Short_t>   ();
    this->initialize<UShort_t>  ();
    this->initialize<Int_t>     ();
    this->initialize<UInt_t>    ();
    this->initialize<Float_t>   ();
//  this->initialize<Float16_t> ();
    this->initialize<Double_t>  ();
//  this->initialize<Double32_t>();
//  this->initialize<Long64_t>  ();
    this->initialize<ULong64_t> ();
    this->initialize<Long_t>    ();
//  this->initialize<ULong_t>   ();
    this->initialize<Bool_t>    ();
}

NtupleFields::~NtupleFields(){
   // TODO
   // deallocate NtupleField elements
}

void NtupleFields::SetBranchAddresses(TTree* tree){
    this->SetBranchAddressesTyped<char*>     (tree);
    this->SetBranchAddressesTyped<Char_t>    (tree);
    this->SetBranchAddressesTyped<UChar_t>   (tree);
    this->SetBranchAddressesTyped<Short_t>   (tree);
    this->SetBranchAddressesTyped<UShort_t>  (tree);
    this->SetBranchAddressesTyped<Int_t>     (tree);
    this->SetBranchAddressesTyped<UInt_t>    (tree);
    this->SetBranchAddressesTyped<Float_t>   (tree);
//  this->SetBranchAddressesTyped<Float16_t> (tree);
    this->SetBranchAddressesTyped<Double_t>  (tree);
//  this->SetBranchAddressesTyped<Double32_t>(tree);
//  this->SetBranchAddressesTyped<Long64_t>  (tree);
    this->SetBranchAddressesTyped<ULong64_t> (tree);
    this->SetBranchAddressesTyped<Long_t>    (tree);
//  this->SetBranchAddressesTyped<ULong_t>   (tree);
    this->SetBranchAddressesTyped<Bool_t>    (tree);
}

void NtupleFields::Branches(TTree* tree){
    this->BranchesTyped<char*>     (tree);
    this->BranchesTyped<Char_t>    (tree);
    this->BranchesTyped<UChar_t>   (tree);
    this->BranchesTyped<Short_t>   (tree);
    this->BranchesTyped<UShort_t>  (tree);
    this->BranchesTyped<Int_t>     (tree);
    this->BranchesTyped<UInt_t>    (tree);
    this->BranchesTyped<Float_t>   (tree);
//  this->BranchesTyped<Float16_t> (tree);
    this->BranchesTyped<Double_t>  (tree);
//  this->BranchesTyped<Double32_t>(tree);
//  this->BranchesTyped<Long64_t>  (tree);
    this->BranchesTyped<ULong64_t> (tree);
    this->BranchesTyped<Long_t>    (tree);
//  this->BranchesTyped<ULong_t>   (tree);
    this->BranchesTyped<Bool_t>    (tree);
}
