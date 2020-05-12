/*
** XIN YUAN, 2020, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "TextPart.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextPart

TextPart::TextPart() : m_wndMain(500, 500, "WmEditor")
{
	//binding
	m_textVM.attach_Model(RefPtr<TextModel>(m_model));
	m_model.AddNotification(m_textVM.get_Notification());

	//properties
	m_wndMain.GetTextEditor().attach_TextBuffer(m_textVM.get_TextBuf());
	m_wndMain.GetTextEditor().UpdateBuffer();

	//commands
	m_wndMain.attach_LoadCommand(m_textVM.get_LoadCommand());
	m_wndMain.attach_SaveCommand(m_textVM.get_SaveCommand());

	//notifications
	m_textVM.AddNotification(m_wndMain.get_Notification());
}

TextPart::~TextPart() noexcept
{
}

MainWindow& TextPart::GetMainWindow() noexcept
{
	return m_wndMain;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
