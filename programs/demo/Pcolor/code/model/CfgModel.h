﻿////////////////////////////////////////////////////////////////////////////////
#ifndef __CFG_MODEL_H__
#define __CFG_MODEL_H__
////////////////////////////////////////////////////////////////////////////////

#include "../common/PcCfg.h"

////////////////////////////////////////////////////////////////////////////////

// CfgModel

class CfgModel : public Proxy_PropertyNotification<CfgModel>
{
public:
	CfgModel();
	CfgModel(const CfgModel&) = delete;
	CfgModel& operator=(const CfgModel&) = delete;
	~CfgModel() noexcept;

	std::shared_ptr<PcCfg> GetCfg() noexcept;

	bool Load(const char* szFile);
	bool Save(const char* szFile);

	bool ModifyColorPoint(size_t index, int gray, int r, int g, int b) noexcept;

private:
	std::shared_ptr<PcCfg> m_spCfg;
};

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
