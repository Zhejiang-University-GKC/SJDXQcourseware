/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../model/TextModel.h"
#include "TextViewModel.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextViewModel

TextViewModel::TextViewModel() noexcept : m_uCookie(0)
{
}
TextViewModel::~TextViewModel() noexcept
{
}

//properties
RefPtr<Fl_Text_Buffer> TextViewModel::get_TextBuf() noexcept
{
	return m_refModel->get_TextBuf();
}

//methods
void TextViewModel::attach_Model(const RefPtr<TextModel>& refModel)
{
	m_refModel = refModel;
	m_uCookie = m_refModel->AddNotification(get_notification());
}

RefPtr<TextModel> TextViewModel::detach_Model() noexcept
{
	m_refModel->RemoveNotification(m_uCookie);
	RefPtr<TextModel> ret = m_refModel;
	m_refModel = RefPtr<TextModel>();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
