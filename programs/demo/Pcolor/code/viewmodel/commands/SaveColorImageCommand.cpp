////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "SaveColorImageCommand.h"

#include "../ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

SaveColorImageCommand::SaveColorImageCommand(ColorViewModel* p) noexcept : m_pVM(p)
{
}

void SaveColorImageCommand::SetParameter(const std::any& param)
{
	m_szFile = std::any_cast<LPCTSTR>(param);
}

void SaveColorImageCommand::Exec()
{
	bool bResult = m_pVM->m_spColorModel->SaveColorImage(m_szFile);
	m_pVM->Fire_OnCommandComplete("Save-Color", bResult);
}

////////////////////////////////////////////////////////////////////////////////
