#pragma once

enum class Type
{
    Box,
    Triangle,
};

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;
    
    Type getType(){ return _type;}
    
protected:
    Type _type;
    int _pointNum;
};
