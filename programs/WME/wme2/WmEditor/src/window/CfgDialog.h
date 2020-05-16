/*
** Mei LiJuan, 2019
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __CFG_DIALOG_H__
#define __CFG_DIALOG_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// CfgDialog

class CfgDialog : public Fl_Window
{
public:
	CfgDialog(int w, int h, const char* t);
	~CfgDialog() noexcept;

public:
//properties
	void attach_BackColor(const RefPtr<Fl_Color>& refColor) noexcept;
	RefPtr<Fl_Color> detach_BackColor() noexcept;

//commands
	void attach_SetBackColorCommand(std::function<bool(Fl_Color)>&& cf) noexcept;
	std::function<bool(Fl_Color)> detach_SetBackColorCommand() noexcept;

//methods
	void Update();

private:
	static void back_color_cb(Fl_Widget* pW, void* pD);
	static void ok_cb(Fl_Widget* pW, void* pD);
	static void cancel_cb(Fl_Widget* pW, void* pD);

private:
	Fl_Box    m_boxBackColor;
	Fl_Button m_btnBackColor;

	Fl_Button m_btnOK;
	Fl_Return_Button m_btnCancel;

//properties
	RefPtr<Fl_Color>  m_refBackColor;

//commands
	std::function<bool(Fl_Color)> m_cmdSetBackColor;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
