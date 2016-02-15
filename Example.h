#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <FEHMotor.h>

class example
{
public:
    example();
    void randfunction();

private:
    int var;
    bool var2;
};

//Making object pointer global
extern example* object;

#endif // EXAMPLE_H
