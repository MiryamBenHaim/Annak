#ifndef __PERSON__
#define __PERSON__

#include "movies.h"
#include "resources.h"

class Person : public Movies {
public:
    Resources r;
};

#endif // __PERSON__