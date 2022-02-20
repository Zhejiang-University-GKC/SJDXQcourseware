////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "ModifyColorPointCommand.h"

#include "../ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

ModifyColorPointCommand::ModifyColorPointCommand(ColorViewModel* p) noexcept : m_pVM(p)
{
}

void ModifyColorPointCommand::SetParameter(const std::any& param)
{
	m_colorPoint = std::any_cast<std::tuple<size_t, int, int, int, int>>(param);
}

void ModifyColorPointCommand::Exec()
{
	bool bResult = m_pVM->m_spCfgModel->ModifyColorPoint(
		std::get<0>(m_colorPoint),
		std::get<1>(m_colorPoint),
		std::get<2>(m_colorPoint),
		std::get<3>(m_colorPoint),
		std::get<4>(m_colorPoint)
		);
	m_pVM->Fire_OnCommandComplete("Modify-Color-Point", bResult);
}

////////////////////////////////////////////////////////////////////////////////
