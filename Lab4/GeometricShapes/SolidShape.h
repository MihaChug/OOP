#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual std::string GetColor()const = 0;
};

