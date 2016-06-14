#pragma once
#include "stdafx.h"

class IShape
{
public:	
	virtual double GetArea()const = 0;
	virtual double GetPerimeter()const = 0;
	virtual std::string ToString()const = 0;
	virtual std::string GetBorderColor()const = 0;
	virtual ~IShape() = default;
};

