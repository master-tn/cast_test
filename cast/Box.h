#pragma once

#include "Object.h"
#include "IWrite.h"

class Box : public Object, public IWrite
{
public:
    Box(int id);
    virtual ~Box() = default;
    
    void print();
    
    virtual void write() override;
    
private:
    int _id;
};
