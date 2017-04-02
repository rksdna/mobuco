#ifndef READREGISTERSFUNCTION_H
#define READREGISTERSFUNCTION_H

#include "Function.h"

class ReadRegistersFunction : public Function
{
public:
    ReadRegistersFunction(const FunctionType &type);
};

class ReadHoldingRegistersFunction : public ReadRegistersFunction
{
public:
    ReadHoldingRegistersFunction();
};

class ReadInputRegistersFunction : public ReadRegistersFunction
{
public:
    ReadInputRegistersFunction();
};

#endif // READREGISTERSFUNCTION_H
