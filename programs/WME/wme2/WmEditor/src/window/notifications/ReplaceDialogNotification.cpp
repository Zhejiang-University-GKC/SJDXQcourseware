﻿/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../../common/TextDef.h"
#include "../ReplaceDialog.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// ReplaceDialog

PropertyNotification ReplaceDialog::get_Notification()
{
	return [this](uint32_t uID)
				{
					if ( uID == PROPID_BACK_COLOR ) {
						this->color(*(this->m_refBackColor));
						this->redraw();
					}
				};
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
