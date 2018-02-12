#include "Meta.h"
#include <string>

//===========================================================================
void find_replace(std::string & str, const std::string & s, const std::string & r) {
    std::string::size_type pos = 0;
    while ((pos = str.find(s, pos)) != std::string::npos) {
        str.replace(pos, s.size(), r);
        pos++;
    }
}

//=====================================s======================================
int main () {
    typedef Renderer<200, 200> MyRenderer;


    std::string filename = "Image - " __DATE__ " - " __TIME__ ".tga";
    find_replace(filename, ":", "_");

    MyRenderer::Save(filename.c_str());

}