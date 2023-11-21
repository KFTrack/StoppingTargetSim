// Ed Callaghan
// Wrapper for yaml representation
// November 2023

#include <ryml.hpp>

// ryml has thought the data structure through more thoroughly then we may
// ever hope to
//typedef ryml::ConstNodeRef YamlNode;

class YamlNode: public ryml::ConstNodeRef{
  public:
    YamlNode();
    YamlNode(ryml::ConstNodeRef node);
   ~YamlNode();

    YamlNode operator[](std::string key);

    template<typename T>
    T Value(std::string key);
  protected:
    /**/
  private:
    /**/
};
