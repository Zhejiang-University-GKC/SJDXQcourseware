////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "LoadCfgCommand.h"

#include "../ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

LoadCfgCommand::LoadCfgCommand(ColorViewModel* p) noexcept : m_pVM(p)
{
}

void LoadCfgCommand::SetParameter(const std::any& param)
{
	m_szFile = std::any_cast<const char*>(param);
}

void LoadCfgCommand::Exec()
{
	bool bResult = m_pVM->m_spCfgModel->Load(m_szFile);
	m_pVM->Fire_OnCommandComplete("Load-Cfg", bResult);
}

////////////////////////////////////////////////////////////////////////////////
