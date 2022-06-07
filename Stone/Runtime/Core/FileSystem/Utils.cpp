#include "Utils.h"

namespace Stone
{
    std::string getDirectoryPath(const std::string& filepath)
    {
        auto lPos = filepath.find_last_of("/");
        std::string directpath = filepath.substr(0, lPos + 1);
        return directpath;
    }
}