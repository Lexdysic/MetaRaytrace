#include "Meta.h"
#include <string.h>

//===========================================================================
void find_replace (char * str, char what, char with) {
    for (char * it = str; *it != '\0'; ++it) {
        if (*it == what)
            *it = with;
    }
}

//=====================================s======================================
int main () {
    typedef Renderer<100, 100> MyRenderer;

    char filename[64];
    strcpy(filename, "Image - " __DATE__ " - " __TIME__ ".tga");
    find_replace(filename, ':', '_');

    MyRenderer::Save(filename);

}