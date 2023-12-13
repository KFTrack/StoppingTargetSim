// Teja Nivarthi
// User-level detector construction parser
// December 2023

#include <StoppingTargetConfigParser.h>
using namespace std;

StoppingTargetConfigParser::StoppingTargetConfigParser(){
    /**/
}

StoppingTargetConfigParser::~StoppingTargetConfigParser(){
    /**/
}

G4VSolid* StoppingTargetConfigParser::CreateBooleanSolid(const YamlNode& config) {
    YamlNode node = YamlNode(config);

    int pos = node["position"].Value<int>();
    string material = node["material"].Value<string>();
    string type = node["type"].Value<string>();

    printf("type: %s, position: %d, material: %s\n", type.c_str(), pos, material.c_str());

    return nullptr;
}