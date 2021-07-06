/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "TextApp.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextApp

TextApp::TextApp() : m_uBackColorCookie(0)
{
}

TextApp::~TextApp() noexcept
{
}

//methods
bool TextApp::Init()
{
	//properties
	m_textPart.GetMainWindow().attach_BackColor(m_cfgPart.GetViewModel().get_BackColor());
	m_textPart.GetMainWindow().Update();
	//commands
	m_textPart.GetMainWindow().attach_ReplaceCommand(get_ReplaceCommand());
	m_textPart.GetMainWindow().attach_ConfigCommand(get_ConfigCommand());
	m_textPart.GetMainWindow().attach_CloseCommand(get_CloseReplaceCommand());
	//notifications
	m_cfgPart.GetViewModel().AddNotification(m_textPart.GetMainWindow().get_Notification());
	return true;
}

int TextApp::Run()
{
	Fl::visual(FL_DOUBLE | FL_RGB);
	m_textPart.GetMainWindow().show();
	return Fl::run();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
