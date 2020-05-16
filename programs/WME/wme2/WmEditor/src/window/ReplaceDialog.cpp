/*
** Mei LiJuan, 2019
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "ReplaceDialog.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// ReplaceDialog

ReplaceDialog::ReplaceDialog(int w, int h, const char* t) : Fl_Window(w, h, t),
															m_replaceFind(80, 10, 210, 25, "Find:"),
															m_replaceWith(80, 40, 210, 25, "Replace:"),
															m_replaceAll(10, 70, 90, 25, "Replace All"),
															m_replaceNext(105, 70, 120, 25, "Replace Next"),
															m_replaceCancel(230, 70, 60, 25, "Cancel")
{
	end();
	set_non_modal();
	callback((Fl_Callback*)&close_cb, &m_cmdClose);
    /*replace_find->align(FL_ALIGN_LEFT);
    replace_with->align(FL_ALIGN_LEFT);
    replace_all->callback((Fl_Callback *)replall_cb, this);
    replace_next->callback((Fl_Callback *)replace2_cb, this);
    replace_cancel->callback((Fl_Callback *)replcan_cb, this);*/
}

ReplaceDialog::~ReplaceDialog() noexcept
{
}

//properties
void ReplaceDialog::attach_BackColor(const RefPtr<Fl_Color>& refColor) noexcept
{
	m_refBackColor = refColor;
}
RefPtr<Fl_Color> ReplaceDialog::detach_BackColor() noexcept
{
	RefPtr<Fl_Color> ret = m_refBackColor;
	m_refBackColor = RefPtr<Fl_Color>();
	return ret;
}

//commands
void ReplaceDialog::attach_CloseCommand(std::function<void()>&& cf) noexcept
{
	m_cmdClose = std::move(cf);
}
std::function<void()> ReplaceDialog::detach_CloseCommand() noexcept
{
	std::function<void()> ret = std::move(m_cmdClose);
	return ret;
}

//methods
void ReplaceDialog::Update()
{
	this->color(*m_refBackColor);
}

//callbacks

void ReplaceDialog::close_cb(Fl_Window* pW, void* pD)
{
	Fl::add_idle(&close_idle_hd, pD);
	default_callback(pW, pD);
}

void ReplaceDialog::close_idle_hd(void* pD)
{
	std::function<void()>& cmd = *((std::function<void()>*)pD);
	if( cmd != nullptr )
		cmd();
	Fl::remove_idle(&close_idle_hd, pD);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
