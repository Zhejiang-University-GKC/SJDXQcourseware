////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "CfgModel.h"

////////////////////////////////////////////////////////////////////////////////

// CfgModel

CfgModel::CfgModel() : m_spCfg(std::make_shared<PcCfg>())
{
}
CfgModel::~CfgModel() noexcept
{
}

std::shared_ptr<PcCfg> CfgModel::GetCfg() noexcept
{
	return m_spCfg;
}

bool CfgModel::Load(const char* szFile)
{
	PcCfg cfg;
	if ( !cfg.Load(szFile) )
		return false;
	*m_spCfg = std::move(cfg);
	Fire_OnPropertyChanged("Cfg");
	return true;
}

bool CfgModel::Save(const char* szFile)
{
	return m_spCfg->Save(szFile);
}

bool CfgModel::ModifyColorPoint(size_t index, int gray, int r, int g, int b) noexcept
{
	if ( index >= m_spCfg->GetCount() )
		return false;
	m_spCfg->SetGrayAt(index, gray);
	m_spCfg->SetRAt(index, r);
	m_spCfg->SetGAt(index, g);
	m_spCfg->SetBAt(index, b);
	Fire_OnPropertyChanged("Cfg");
	return true;
}

////////////////////////////////////////////////////////////////////////////////
