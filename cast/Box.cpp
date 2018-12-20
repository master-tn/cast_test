#include "Box.h"
#include <iostream>

Box::Box(int id)
: Object()
, _id(id)
{
    _type = Type::Box;
    _pointNum = 8;
}

void Box::print()
{
    std::cout << "id=" << _id << " pointNum=" << _pointNum << std::endl;
}

void Box::write()
{
    this->print();
}
