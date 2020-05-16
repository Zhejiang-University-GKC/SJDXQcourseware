﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../common/TextDef.h"

#include "CfgModel.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// CfgModel

CfgModel::CfgModel() noexcept
{
	uchar r, g, b;
	Fl::get_color(FL_BACKGROUND_COLOR, r, g, b);
	m_clrBack.Set(r, g, b);
}
CfgModel::~CfgModel() noexcept
{
}

//methods
const RgbColor& CfgModel::GetBackColor() const noexcept
{
	return m_clrBack;
}

void CfgModel::SetBackColor(const RgbColor& clr)
{
	if ( m_clrBack != clr ) {
		m_clrBack = clr;
		Fire(PROPID_BACK_COLOR);
	}
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
