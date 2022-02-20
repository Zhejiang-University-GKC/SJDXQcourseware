////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "SaveCfgCommand.h"

#include "../ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

SaveCfgCommand::SaveCfgCommand(ColorViewModel* p) noexcept : m_pVM(p)
{
}

void SaveCfgCommand::SetParameter(const std::any& param)
{
	m_szFile = std::any_cast<const char*>(param);
}

void SaveCfgCommand::Exec()
{
	bool bResult = m_pVM->m_spCfgModel->Save(m_szFile);
	m_pVM->Fire_OnCommandComplete("Save-Cfg", bResult);
}

////////////////////////////////////////////////////////////////////////////////
