////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "LoadGrayImageCommand.h"

#include "../ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

LoadGrayImageCommand::LoadGrayImageCommand(ColorViewModel* p) noexcept : m_pVM(p)
{
}

void LoadGrayImageCommand::SetParameter(const std::any& param)
{
	m_szFile = std::any_cast<LPCTSTR>(param);
}

void LoadGrayImageCommand::Exec()
{
	bool bResult = m_pVM->m_spColorModel->LoadGrayImage(m_szFile);
	m_pVM->Fire_OnCommandComplete("Load-Gray", bResult);
}

////////////////////////////////////////////////////////////////////////////////
