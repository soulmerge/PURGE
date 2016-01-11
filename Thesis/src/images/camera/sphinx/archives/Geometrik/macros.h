#ifndef MACROS_H
#define MACROS_H 1

#include <string>
#include <sstream>

inline std::string ITOA(int i) {
    std::stringstream s;
    s << i;
    return s.str();
}

#define DEBUG_LOG(X) Ogre::LogManager::getSingleton().logMessage(X)
#define TRACE(X)     Ogre::LogManager::getSingleton().logMessage(X)
// #define ITOA(X)      do {std::stringstream s; s std::string() + (X)} while (0)

#endif /* MACROS_H */

