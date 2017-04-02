#include "FunctionType.h"
#include "ReadRegistersFunction.h"

ReadRegistersFunction::ReadRegistersFunction(const FunctionType *type)
    : Function(type)
{
}

static CustomFunctionType<ReadHoldingRegistersFunction> readHoldingRegistersType(0x03, Function::tr("Read holding registers"));

ReadHoldingRegistersFunction::ReadHoldingRegistersFunction()
    : ReadRegistersFunction(&readHoldingRegistersType)
{
}

static CustomFunctionType<ReadHoldingRegistersFunction> readInputRegistersType(0x04, Function::tr("Read input registers"));

ReadInputRegistersFunction::ReadInputRegistersFunction()
    : ReadRegistersFunction(&readInputRegistersType)
{
}
