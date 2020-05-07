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

	//properties
	m_wndMain.GetTextEditor().attach_TextBuffer(m_textVM.get_TextBuf());

	//commands
	m_wndMain.attach_LoadCommand(m_textVM.get_LoadCommand());
	m_wndMain.attach_SaveCommand(m_textVM.get_SaveCommand());

	//notifications
	m_textVM.AddNotification(m_wndMain.get_Notification());
}

TextPart::~TextPart() noexcept
{
}

void TextPart::attach_ReplaceCommand(std::function<bool()>&& cf) noexcept
{
	m_wndMain.attach_ReplaceCommand(std::move(cf));
}
std::function<bool()> TextPart::detach_ReplaceCommand() noexcept
{
	return m_wndMain.detach_ReplaceCommand();
}

void TextPart::Show()
{
	m_wndMain.show();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
