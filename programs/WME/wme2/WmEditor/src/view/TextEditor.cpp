/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "TextEditor.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextEditor

TextEditor::TextEditor(int x, int y, int w, int h, const char* l) : Fl_Text_Editor(x, y, w, h, l)
{
}

TextEditor::~TextEditor() noexcept
{
}

//properties
void TextEditor::attach_TextBuffer(const RefPtr<Fl_Text_Buffer>& refBuffer) noexcept
{
	m_refBuffer = refBuffer;
}
RefPtr<Fl_Text_Buffer> TextEditor::detach_TextBuffer() noexcept
{
	RefPtr<Fl_Text_Buffer> ret = m_refBuffer;
	m_refBuffer = RefPtr<Fl_Text_Buffer>();
	return ret;
}

void TextEditor::UpdateBuffer()
{
	this->buffer(m_refBuffer.Get());
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
