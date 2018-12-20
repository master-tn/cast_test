#pragma once

#include "Object.h"
#include "IWrite.h"

class Triangle : public Object, public IWrite
{
public:
    Triangle(int id);
    virtual ~Triangle() = default;
    
    void put();
    
    virtual void write() override;
    
private:
    int _id;
};
