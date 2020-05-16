/*
** XIN YUAN, 2020, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../TextApp.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextApp

std::function<bool()> TextApp::get_ReplaceCommand()
{
	return [this]()->bool
			{
				if( this->m_upReplacePart.get() == nullptr ) {
					this->m_upReplacePart = std::unique_ptr<ReplacePart>(new ReplacePart);
					//properties
					this->m_upReplacePart->GetReplaceDialog().attach_BackColor(this->m_cfgPart.GetViewModel().get_BackColor());
					this->m_upReplacePart->GetReplaceDialog().Update();
					//commands
					this->m_upReplacePart->GetReplaceDialog().attach_CloseCommand(this->get_CloseReplaceCommand());
					//notifications
					this->m_uBackColorCookie = this->m_cfgPart.GetViewModel().AddNotification(this->m_upReplacePart->GetReplaceDialog().get_Notification());
				}
				this->m_upReplacePart->GetReplaceDialog().show();
				return true;
			};
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
