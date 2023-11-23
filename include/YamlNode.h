// Ed Callaghan
// Wrapper for yaml representation
// November 2023

#ifndef YAMLNODE_H
#define YAMLNODE_H

#include <ryml.hpp>

// ryml has thought the data structure through more thoroughly then we may
// ever hope to. we just sprinkle a few conveniences on top :)
class YamlNode: public ryml::ConstNodeRef{
  public:
    YamlNode();
    YamlNode(ryml::ConstNodeRef node);
   ~YamlNode();

    YamlNode operator[](std::string key);

//  template<typename T>
//  T Value(std::string key);
    template<typename T>
    T Value();
  protected:
    /**/
  private:
    /**/
};

#endif
