// Ed Callaghan
// Wrapper for yaml parser
// November 2023

#include <fstream>
#include <string>
#include <vector>
#include <ryml.hpp>
#include <YamlNode.h>

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
