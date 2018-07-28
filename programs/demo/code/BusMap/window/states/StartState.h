
#pragma once

#include "etlbase.h"

#include "StateDef.h"

class StartState : public IStateBase
{
public:
	//IStateBase methods
	virtual int Process(unsigned int uEvent, std::any& param);
};
