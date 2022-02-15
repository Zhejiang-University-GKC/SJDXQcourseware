////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

class LabelCtrl : public CWindowImpl<LabelCtrl, CStatic>
{
public:
	LabelCtrl() : m_clrText(RGB(0, 0, 0)), m_clrBack(CLR_INVALID)
	{
	}

	std::shared_ptr<CString> m_spLabel;

	COLORREF m_clrText;
	COLORREF m_clrBack;
	CBrush   m_bshBack;

	std::shared_ptr<CString> GetLabel() throw()
	{
		return m_spLabel;
	}
	void set_Label(const std::shared_ptr<CString>& sp) throw()
	{
		m_spLabel = sp;
	}

	void Update() throw()
	{
		SetWindowText(*m_spLabel);
	}

	void SetColor(COLORREF clrText, COLORREF clrBack) throw()
	{
		m_clrText = clrText;
		if( m_clrBack != clrBack ) {
			if( !m_bshBack.IsNull() )
				m_bshBack.DeleteObject();
			m_bshBack.CreateSolidBrush(clrBack);
			m_clrBack = clrBack;
		}
	}

//------------------------------------------------------------------------------
//message handler
	BEGIN_MSG_MAP(LabelCtrl)
		MESSAGE_HANDLER(OCM_CTLCOLORSTATIC, OnCtlColorStatic)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
//------------------------------------------------------------------------------

	LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HDC hDC = (HDC)wParam;
		HWND hWnd = (HWND)lParam;

	    SetTextColor(hDC, m_clrText);  // text Color
		SetBkColor(hDC, m_clrBack);  // text BkColor

		bHandled = TRUE;

		return (LRESULT)m_bshBack.m_hBrush;
	}
};

////////////////////////////////////////////////////////////////////////////////
