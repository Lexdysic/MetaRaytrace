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

//===========================================================================
int main () {
    typedef Renderer<100, 100> MyRenderer;


    std::string filename = "Image - " __DATE__ " - " __TIME__ ".tga";
    find_replace(filename, ":", "_");

    MyRenderer::Save(filename.c_str());

}