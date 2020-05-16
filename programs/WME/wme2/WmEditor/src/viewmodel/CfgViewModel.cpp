/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../common/TextDef.h"
#include "../model/CfgModel.h"
#include "CfgViewModel.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// CfgViewModel

CfgViewModel::CfgViewModel() noexcept : m_clrBack(FL_BACKGROUND_COLOR)
{
}
CfgViewModel::~CfgViewModel() noexcept
{
}

//properties
RefPtr<Fl_Color> CfgViewModel::get_BackColor() noexcept
{
	return RefPtr<Fl_Color>(m_clrBack);
}

//methods
void CfgViewModel::attach_Model(const RefPtr<CfgModel>& refModel) noexcept
{
	m_refModel = refModel;
}

RefPtr<CfgModel> CfgViewModel::detach_Model() noexcept
{
	return RefPtr<CfgModel>(std::move(m_refModel));
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
