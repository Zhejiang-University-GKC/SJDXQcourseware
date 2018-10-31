////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#define ICN_PIXEL  (0x100)

struct NMIMAGEPIXEL
{
	NMHDR    nmh;  // Contains information about a notification message.
	int      x, y;
	COLORREF rgb;  // The COLORREF value is used to specify an RGB color.
};

template <class T>
class ATL_NO_VTABLE ImageCtrlImpl : public ATL::CWindowImpl<T, CWindowEx, ATL::CControlWinTraits>,
									public CScrollImpl<T>
{
public:
	DECLARE_WND_CLASS(NULL)

//------------------------------------------------------------------------------
	bool m_bEnter;  //mouse enter

	std::shared_ptr<CImage> m_spImage;

	ImageCtrlImpl() throw() : m_bEnter(false)
	{
	}

	std::shared_ptr<CImage> GetImage() throw()
	{
		return m_spImage;
	}
	void set_Image(const std::shared_ptr<CImage>& sp) throw()
	{
		m_spImage = sp;
	}
	bool is_image_null() const throw()
	{
		return m_spImage.get() == NULL || m_spImage->IsNull();
	}

	void UpdateScroll() throw()
	{
		int cx = 1;
		int cy = 1;
		if( !is_image_null() ) {
			cx = m_spImage->GetWidth();
			cy = m_spImage->GetHeight();
		}
		SetScrollSize(cx, cy, TRUE, false);//设置滚动视图的大小
	}

//------------------------------------------------------------------------------
//message handler
	BEGIN_MSG_MAP(ImageCtrlImpl)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		CHAIN_MSG_MAP(CScrollImpl<T>)
	END_MSG_MAP()

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CDCHandle dc((HDC)wParam);
		RECT rcClient;
		GetClientRect(&rcClient);
		CBrush bsh;
		bsh.CreateSolidBrush(RGB(64, 64, 64));
		dc.FillRect(&rcClient, bsh);
		return 1;
	}
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int iCode = LOWORD(lParam);
		if( iCode == HTCLIENT && !is_image_null() ) {
			::SetCursor(::LoadCursor(NULL, IDC_CROSS));
			bHandled = TRUE;
			return 1;
		}
		return 0;
	}
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UINT uFlags = (UINT)wParam;
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		POINT pt;
		GetScrollOffset(pt);
		if( !m_bEnter ) {
			m_bEnter = StartTrackMouseLeave() ? true : false;
		}
		if( is_image_null() )
			return 0;
		NMIMAGEPIXEL nm;
		nm.nmh.code = ICN_PIXEL;
		nm.nmh.idFrom = GetDlgCtrlID();
		nm.nmh.hwndFrom = m_hWnd;
		nm.x = x + pt.x;
		nm.y = y + pt.y;
		nm.rgb = CLR_INVALID;
		if( (nm.x < m_spImage->GetWidth()) && (nm.y < m_spImage->GetHeight()) )
			nm.rgb = m_spImage->GetPixel(nm.x, nm.y);
		SendMessage(GetParent(), WM_NOTIFY, nm.nmh.idFrom, (LPARAM)&nm);
		return 0;
	}
	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		NMIMAGEPIXEL nm;
		nm.nmh.code = ICN_PIXEL;
		nm.nmh.idFrom = GetDlgCtrlID();
		nm.nmh.hwndFrom = m_hWnd;
		nm.x = 0;
		nm.y = 0;
		nm.rgb = CLR_INVALID;
		SendMessage(GetParent(), WM_NOTIFY, nm.nmh.idFrom, (LPARAM)&nm);
		//cancel
		if( CancelTrackMouse(TME_LEAVE) )
			m_bEnter = false;
		return 0;
	}

//------------------------------------------------------------------------------
// Overrideables
	void DoPaint(CDCHandle dc)
	{
		if( !is_image_null() ) {
			int nOldMode = dc.SetStretchBltMode(COLORONCOLOR);
			m_spImage->Draw(dc, _WTYPES_NS::CRect(0, 0, m_spImage->GetWidth(), m_spImage->GetHeight()));
			dc.SetStretchBltMode(nOldMode);
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
