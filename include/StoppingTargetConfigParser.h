// Teja Nivarthi
// User-level detector construction parser
// December 2023

#include <G4VSolid.hh>
#include <YamlParser.h>

class StoppingTargetConfigParser {
    public:
      StoppingTargetConfigParser();
     ~StoppingTargetConfigParser();

     G4VSolid* CreateBooleanSolid(const YamlNode& config);
    protected:
    /**/
    private:
    /**/
};