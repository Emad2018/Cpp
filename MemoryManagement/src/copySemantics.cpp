
#include <cstdlib>
#include "copySemantics.hpp"
#include <iostream>
DefaultCopy::DefaultCopy(/* args */)
{
    _myInt = (int *)malloc(sizeof(int));
}
DefaultCopy::~DefaultCopy()
{
}
void DefaultCopy::printOwnAddress()
{
    std::cout << "Own address on the stack is " << this << std::endl;
}
void DefaultCopy::printMemberAddress()
{
    std::cout << "Managing memory block on the heap at " << _myInt << std::endl;
}
NoCopy::NoCopy()
{
}
NoCopy::~NoCopy()
{
}
ExclusiveCopy::ExclusiveCopy(/* args */)
{
    _myInt = (int *)malloc(sizeof(int));
    std::cout << "Exclusive resource allocated" << std::endl;
}

ExclusiveCopy::~ExclusiveCopy()
{
    if (_myInt != nullptr)
    {
        free(_myInt);
        std::cout << "ExclusiveCopy resource freed" << std::endl;
    }
}
ExclusiveCopy::ExclusiveCopy(ExclusiveCopy &source)
{
    _myInt = source._myInt;
    source._myInt = nullptr;
}
ExclusiveCopy &ExclusiveCopy::operator=(ExclusiveCopy &source)
{
    _myInt = source._myInt;
    source._myInt = nullptr;
    return *this;
}
ExclusiveCopy::ExclusiveCopy(ExclusiveCopy &&source)
{
}
ExclusiveCopy &ExclusiveCopy::operator=(ExclusiveCopy &&source)
{
}
void ExclusiveCopy::printOwnAddress()
{
    std::cout << "ExclusiveCopy : Own address on the stack is " << this << std::endl;
}
void ExclusiveCopy::printMemberAddress()
{
    std::cout << "ExclusiveCopy : Managing memory block on the heap at " << _myInt << std::endl;
}

DeepCopy::DeepCopy(int val)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = val;
    std::cout << "resource allocated at address " << _myInt << std::endl;
}

DeepCopy::~DeepCopy()
{
    free(_myInt);
    std::cout << "DeepCopy resource freed at address " << _myInt << std::endl;
}
DeepCopy::DeepCopy(DeepCopy &source)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = *source._myInt;
    std::cout << "resource allocated at address " << _myInt << " with _myInt = " << *_myInt << std::endl;
}
DeepCopy &DeepCopy::operator=(DeepCopy &source)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = *source._myInt;
    std::cout << "resource allocated at address " << _myInt << " with _myInt = " << *_myInt << std::endl;
    return *this;
}
DeepCopy::DeepCopy(DeepCopy &&source)
{
}
DeepCopy &DeepCopy::operator=(DeepCopy &&source)
{
}
int SharedCopy::_cnt = 0;
SharedCopy::SharedCopy(int val)
{
    _myInt = (int *)malloc(sizeof(int));
    *_myInt = val;
    ++_cnt;
    std::cout << "resource allocated at address " << _myInt << std::endl;
}

SharedCopy::~SharedCopy()
{
    --_cnt;
    if (_cnt == 0)
    {
        free(_myInt);
        std::cout << "SharedCopy resource freed at address " << _myInt << std::endl;
    }
    else
    {
        std::cout << "instance at address " << this << " goes out of scope with _cnt = " << _cnt << std::endl;
    }
}
SharedCopy::SharedCopy(SharedCopy &source)
{
    _myInt = source._myInt;
    ++_cnt;
    std::cout << _cnt << " instances with handles to address " << _myInt << " with _myInt = " << *_myInt << std::endl;
}
SharedCopy &SharedCopy::operator=(SharedCopy &source)
{
    _myInt = source._myInt;
    ++_cnt;
    std::cout << _cnt << " instances with handles to address " << _myInt << " with _myInt = " << *_myInt << std::endl;
    return *this;
}
SharedCopy::SharedCopy(SharedCopy &&source)
{
}
SharedCopy &SharedCopy::operator=(SharedCopy &&source)
{
}