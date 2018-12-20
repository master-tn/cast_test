#include "Triangle.h"
#include <iostream>

Triangle::Triangle(int id)
: Object()
, _id(id)
{
    _type = Type::Triangle;
    _pointNum = 3;
}

void Triangle::put()
{
     std::cout << "id=" << _id << " pointNum=" << _pointNum << std::endl;
}

void Triangle::write()
{
    this->put();
}
