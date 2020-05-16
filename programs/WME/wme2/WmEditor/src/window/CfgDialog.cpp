/*
** Mei LiJuan, 2019
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "CfgDialog.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// CfgDialog

CfgDialog::CfgDialog(int w, int h, const char* t) : Fl_Window(w, h, t),
													m_boxBackColor(FL_FLAT_BOX, 10, 10, 150, 25, "Back"),
													m_btnBackColor(160, 10, 30, 25, "..."),
													m_btnOK(10, 100, 60, 25, "OK"),
													m_btnCancel(90, 100, 80, 25, "Cancel")
{
	end();
	set_modal();

	m_btnBackColor.callback(&back_color_cb, this);
	m_btnOK.callback(&ok_cb, this);
	m_btnCancel.callback(&cancel_cb, this);
}

CfgDialog::~CfgDialog() noexcept
{
}

//properties
void CfgDialog::attach_BackColor(const RefPtr<Fl_Color>& refColor) noexcept
{
	m_refBackColor = refColor;
}
RefPtr<Fl_Color> CfgDialog::detach_BackColor() noexcept
{
	RefPtr<Fl_Color> ret = m_refBackColor;
	m_refBackColor = RefPtr<Fl_Color>();
	return ret;
}

//commands
void CfgDialog::attach_SetBackColorCommand(std::function<bool(Fl_Color)>&& cf) noexcept
{
	m_cmdSetBackColor = std::move(cf);
}
std::function<bool(Fl_Color)> CfgDialog::detach_SetBackColorCommand() noexcept
{
	std::function<bool(Fl_Color)> ret = std::move(m_cmdSetBackColor);
	return ret;
}

//methods
void CfgDialog::Update()
{
	m_boxBackColor.color(*m_refBackColor);
	m_boxBackColor.labelcolor(fl_contrast(*m_refBackColor, *m_refBackColor));
}

//callbacks

void CfgDialog::back_color_cb(Fl_Widget* pW, void* pD)
{
	CfgDialog* pThis = (CfgDialog*)pD;
	uchar r, g, b;
	Fl::get_color(pThis->m_boxBackColor.color(), r, g, b);
	if( fl_color_chooser("Select color", r, g, b, -1) != 0 ) {
		Fl_Color clrNew = fl_rgb_color(r, g, b);
		pThis->m_boxBackColor.color(clrNew);
		pThis->m_boxBackColor.labelcolor(fl_contrast(clrNew, clrNew));
		pThis->m_boxBackColor.redraw();
	}
}
void CfgDialog::ok_cb(Fl_Widget* pW, void* pD)
{
	CfgDialog* pThis = (CfgDialog*)pD;
	std::function<bool(Fl_Color)>& cf = pThis->m_cmdSetBackColor;
	if ( cf != nullptr )
		cf(pThis->m_boxBackColor.color());
	pThis->hide();
}
void CfgDialog::cancel_cb(Fl_Widget* pW, void* pD)
{
	CfgDialog* pThis = (CfgDialog*)pD;
	pThis->hide();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
