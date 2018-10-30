#pragma once
#include <string>

class ISerialize
{
public:
	virtual std::string& Serialize() = 0;
	virtual ~ISerialize();
};
