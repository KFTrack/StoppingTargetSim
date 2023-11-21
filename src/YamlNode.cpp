// Ed Callaghan
// Wrapper for yaml representation
// November 2023

#include <YamlNode.h>

YamlNode::YamlNode(){
    /**/
}

YamlNode::YamlNode(ryml::ConstNodeRef node): ryml::ConstNodeRef(node){
    /**/
}

YamlNode::~YamlNode(){
    /**/
}

// must construct from underlying ryml type in order for nested maps
// to be retain value look-up at each level
YamlNode YamlNode::operator[](std::string key){
    YamlNode rv(static_cast<ryml::ConstNodeRef>(*this)[key.c_str()]);
    return rv;
}

// specializations below offer a convenient abstraction of c4::* conversions
template<>
int YamlNode::Value(std::string key){
    int rv;
    c4::atoi((*this)[key.c_str()].val(), &rv);
    return rv;
}

template<>
unsigned int YamlNode::Value(std::string key){
    unsigned int rv;
    c4::atou((*this)[key.c_str()].val(), &rv);
    return rv;
}

template<>
float YamlNode::Value(std::string key){
    float rv;
    c4::atof((*this)[key.c_str()].val(), &rv);
    return rv;
}

template<>
double YamlNode::Value(std::string key){
    double rv;
    c4::atod((*this)[key.c_str()].val(), &rv);
    return rv;
}

// woefully inefficient "freshman-copy" of string in stl container
template<>
std::string YamlNode::Value(std::string key){
    std::string rv = "";
    auto c4val = (*this)[key.c_str()].val();
    for (unsigned int i = 0 ; i < c4val.size() ; i++){
        rv += c4val[i];
    }

    return rv;
}
