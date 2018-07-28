
#pragma once

#include "etlbase.h"

#include "StateDef.h"

class CaptureState : public IStateBase
{
public:
	//IStateBase methods
	virtual int Process(unsigned int uEvent, std::any& param);
};
