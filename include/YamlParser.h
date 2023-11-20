// Ed Callaghan
// Wrapper for yaml parser and representation
// November 2023

#include <fstream>
#include <string>
#include <vector>
#include <ryml.hpp>

// ryml has thought the data structure through more thoroughly then we may
// ever hope to
typedef ryml::ConstNodeRef YamlNode;

std::string read_file(std::string path);
ryml::Tree parse_yaml(std::string buffer);

class YamlParser{
  public:
    YamlParser();
   ~YamlParser();

    YamlNode Parse(std::string path);
  protected:
    // retain all parsed trees for object lifetime
    std::vector<ryml::Tree> trees;
  private:
    /**/
};
