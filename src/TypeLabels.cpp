// Ed Callaghan
// Forward mapping from typenames to string labels
// This is the mechanism upon which ``type-iteration'' rests, hacky as it is

#include <TypeLabels.h>

std::string GetTypeCode(std::string label){
    std::string rv = "void";
    if (label == "char*"){
        rv = "C";
    }
    else if (label == "Char_t"){
        rv = "B";
    }
    else if (label == "UChar_t"){
        rv = "b";
    }
    else if (label == "Short_t"){
        rv = "S";
    }
    else if (label == "UShort_t"){
        rv = "s";
    }
    else if (label == "Int_t"){
        rv = "I";
    }
    else if (label == "UInt_t"){
        rv = "i";
    }
    else if (label == "Float_t"){
        rv = "F";
    }
    else if (label == "Double_t"){
        rv = "D";
    }
    else if (label == "Long64_t"){
        rv = "L";
    }
    else if (label == "ULong64_t"){
        rv = "l";
    }
    else if (label == "Long_t"){
        rv = "G";
    }
    else if (label == "ULong_t"){
        rv = "g";
    }
    else if (label == "Bool_t"){
        rv = "O";
    }
    return rv;
}

/*
template<typename T>
std::string GetTypeLabel(){
    std::string rv = "";
    return rv;
}
*/

template<>
std::string GetTypeLabel<char*>(){
    std::string rv = "char*";
    return rv;
}

template<>
std::string GetTypeLabel<const char*>(){
    std::string rv = "char*";
    return rv;
}

template<>
std::string GetTypeLabel<Char_t>(){
    std::string rv = "Char_t";
    return rv;
}

template<>
std::string GetTypeLabel<UChar_t>(){
    std::string rv = "UChar_t";
    return rv;
}

template<>
std::string GetTypeLabel<Short_t>(){
    std::string rv = "Short_t";
    return rv;
}

template<>
std::string GetTypeLabel<UShort_t>(){
    std::string rv = "UShort_t";
    return rv;
}

template<>
std::string GetTypeLabel<Int_t>(){
    std::string rv = "Int_t";
    return rv;
}

template<>
std::string GetTypeLabel<UInt_t>(){
    std::string rv = "UInt_t";
    return rv;
}

template<>
std::string GetTypeLabel<Float_t>(){
    std::string rv = "Float_t";
    return rv;
}

template<>
std::string GetTypeLabel<Double_t>(){
    std::string rv = "Double_t";
    return rv;
}

template<>
std::string GetTypeLabel<Long64_t>(){
    std::string rv = "Long64_t";
    return rv;
}

template<>
std::string GetTypeLabel<ULong64_t>(){
    std::string rv = "ULong64_t";
    return rv;
}

template<>
std::string GetTypeLabel<Long_t>(){
    std::string rv = "Long_t";
    return rv;
}

template<>
std::string GetTypeLabel<ULong_t>(){
    std::string rv = "ULong_t";
    return rv;
}

template<>
std::string GetTypeLabel<Bool_t>(){
    std::string rv = "Bool_t";
    return rv;
}
