// Ed Callaghan
// Wrapper for yaml parser and representation
// November 2023

#include <YamlParser.h>

// read file contents piecemeal into a single string
std::string read_file(std::string path){
    std::string rv;
    std::ifstream fin(path);
    while (!fin.eof()){
        std::string tmp;
        getline(fin, tmp);
        rv += tmp + '\n';
    }

    return rv;
}

// defer to ryml for parsing the configuration
ryml::Tree parse_yaml(std::string path){
    std::string buffer = read_file(path);
    ryml::Tree rv = ryml::parse_in_arena(ryml::to_csubstr(buffer.c_str()));
    return rv;
}

YamlParser::YamlParser(){
    /**/
}

YamlParser::~YamlParser(){
    /**/
}

YamlNode YamlParser::Parse(std::string path){
    // parse yaml, and retain tree for object lifetime
    this->trees.push_back(parse_yaml(path));

    // but return reference to root node
    ryml::ConstNodeRef root = this->trees.back().rootref();
    YamlNode rv(root);

    return rv;
}
