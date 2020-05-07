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
															m_replaceFind(std::make_shared<Fl_Input>(80, 10, 210, 25, "Find:")),
															m_replaceWith(std::make_shared<Fl_Input>(80, 40, 210, 25, "Replace:")),
															m_replaceAll(std::make_shared<Fl_Button>(10, 70, 90, 25, "Replace All")),
															m_replaceNext(std::make_shared<Fl_Return_Button>(105, 70, 120, 25, "Replace Next")),
															m_replaceCancel(std::make_shared<Fl_Button>(230, 70, 60, 25, "Cancel"))
{
	end();
	set_non_modal();
    /*replace_find->align(FL_ALIGN_LEFT);
    replace_with->align(FL_ALIGN_LEFT);
    replace_all->callback((Fl_Callback *)replall_cb, this);
    replace_next->callback((Fl_Callback *)replace2_cb, this);
    replace_cancel->callback((Fl_Callback *)replcan_cb, this);*/
}

ReplaceDialog::~ReplaceDialog() noexcept
{
}
}