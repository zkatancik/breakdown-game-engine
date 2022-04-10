#ifndef BASE_TAG
#define BASE_TAG

#include <string>

static std::hash<std::string> hash;

const static int BaseTextTag = int(hash("BaseTextTag"));
const static int BaseMouseTag = int(hash("BaseMouseTag"));
const static int BaseButtonTag = int(hash("BaseButtonTag"));

#endif
