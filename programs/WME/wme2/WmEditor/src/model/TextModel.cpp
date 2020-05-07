/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "TextModel.h"

#include "../common/TextDef.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextModel

TextModel::TextModel()
{
}
TextModel::~TextModel() noexcept
{
}

//properties
RefPtr<Fl_Text_Buffer> TextModel::get_TextBuf() noexcept
{
	return RefPtr<Fl_Text_Buffer>(m_textBuffer);
}

//methods
bool TextModel::Load(const std::string& str)
{
	if (m_textBuffer.loadfile(str.c_str()) == 0) {
		Fire(PROPID_TEXT);
		return true;
	}
	return false;
}

bool TextModel::Save(const std::string& str)
{
	if (m_textBuffer.savefile(str.c_str()) == 0) {
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
