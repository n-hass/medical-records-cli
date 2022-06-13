#ifndef MED_GLOBAL_H
#define MED_GLOBAL_H

#include <string>

namespace database { // declared extern so that can be accessed across whole program. Declaration here, definition elsewhere in a source file
    extern std::string path;
    extern unsigned int recordCount;
}

#endif