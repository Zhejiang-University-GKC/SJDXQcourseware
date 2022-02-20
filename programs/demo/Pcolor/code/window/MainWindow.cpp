////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow() : m_spPropertySink(std::make_shared<MainWindowPropertySink>(this)),
						m_spCommandSink(std::make_shared<MainWindowCommandSink>(this))
{
}

//properties

void MainWindow::set_Cfg(const std::shared_ptr<PcCfg>& sp) noexcept
{
	m_spCfg = sp;
}

//commands

void MainWindow::set_LoadGrayCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept
{
	m_cmdLoadGray = cmd;
}
void MainWindow::set_SaveColorCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept
{
	m_cmdSaveColor = cmd;
}
void MainWindow::set_LoadCfgCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept
{
	m_cmdLoadCfg = cmd;
}
void MainWindow::set_SaveCfgCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept
{
	m_cmdSaveCfg = cmd;
}
void MainWindow::set_ModifyColorPointCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept
{
	m_cmdModifyColorPoint = cmd;
}

//notifications

std::shared_ptr<IPropertyNotification> MainWindow::get_PropertySink() noexcept
{
	return std::static_pointer_cast<IPropertyNotification>(m_spPropertySink);
}
std::shared_ptr<ICommandNotification> MainWindow::get_CommandSink() noexcept
{
	return std::static_pointer_cast<ICommandNotification>(m_spCommandSink);
}

//------------------------------------------------------------------------------
LRESULT MainWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//--------------------------------------------------------------------------
	m_btnLoadImage.Create(m_hWnd, rcDefault, _T("Load Image"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_BTN_LOAD_IMAGE);
	m_txtPixel.Create(m_hWnd, rcDefault, _T(""),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_TEXT_PIXEL);
	m_btnSaveImage.Create(m_hWnd, rcDefault, _T("Save Image"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_BTN_SAVE_IMAGE);
	m_imageCtrlOriginal.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_PIC_ORIGINAL);
	m_imageCtrlOriginal.UpdateScroll();
	m_imageCtrlProcess.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_PIC_PROCESS);
	m_imageCtrlProcess.UpdateScroll();
	m_txtGray.Create(m_hWnd, rcDefault, _T("Gray:"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_TEXT_GRAY);
	m_editGray.Create(m_hWnd, rcDefault, _T("0"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
					IDC_EDIT_GRAY);
	m_updGray.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
					IDC_UPDOWN_GRAY);
	m_txtR.Create(m_hWnd, rcDefault, _T("R:"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_TEXT_R);
	m_editR.Create(m_hWnd, rcDefault, _T("0"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
					IDC_EDIT_R);
	m_updR.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
					IDC_UPDOWN_R);
	m_txtG.Create(m_hWnd, rcDefault, _T("G:"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_TEXT_G);
	m_editG.Create(m_hWnd, rcDefault, _T("0"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
					IDC_EDIT_G);
	m_updG.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
					IDC_UPDOWN_G);
	m_txtB.Create(m_hWnd, rcDefault, _T("B:"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_TEXT_B);
	m_editB.Create(m_hWnd, rcDefault, _T("0"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_NUMBER, 0,
					IDC_EDIT_B);
	m_updB.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | UDS_AUTOBUDDY | UDS_SETBUDDYINT, 0,
					IDC_UPDOWN_B);
	m_updGray.SetRange32(0, 255);
	m_updGray.SetPos32(0);
	m_updGray.SetBuddy(m_editGray);
	m_updR.SetRange32(0, 255);
	m_updR.SetPos32(0);
	m_updR.SetBuddy(m_editR);
	m_updG.SetRange32(0, 255);
	m_updG.SetPos32(0);
	m_updG.SetBuddy(m_editG);
	m_updB.SetRange32(0, 255);
	m_updB.SetPos32(0);
	m_updB.SetBuddy(m_editB);
	m_btnLoadCfg.Create(m_hWnd, rcDefault, _T("Load Cfg"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_BTN_LOAD_CFG);
	m_btnSaveCfg.Create(m_hWnd, rcDefault, _T("Save Cfg"),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0,
					IDC_BTN_SAVE_CFG);
	m_listLut.Create(m_hWnd, rcDefault, NULL,
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0,
					IDC_LIST_LUT);
	m_listLut.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES,
										LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listLut.InsertColumn(0, _T("Gray"), LVCFMT_LEFT, 50);
	m_listLut.InsertColumn(1, _T("R"), LVCFMT_LEFT, 50);
	m_listLut.InsertColumn(2, _T("G"), LVCFMT_LEFT, 50);
	m_listLut.InsertColumn(3, _T("B"), LVCFMT_LEFT, 50);
	//start state
	m_btnSaveImage.EnableWindow(FALSE);
	m_editGray.EnableWindow(FALSE);
	m_updGray.EnableWindow(FALSE);
	m_editR.EnableWindow(FALSE);
	m_updR.EnableWindow(FALSE);
	m_editG.EnableWindow(FALSE);
	m_updG.EnableWindow(FALSE);
	m_editB.EnableWindow(FALSE);
	m_updB.EnableWindow(FALSE);
	m_btnLoadCfg.EnableWindow(FALSE);
	m_btnSaveCfg.EnableWindow(FALSE);
	m_listLut.EnableWindow(FALSE);
	//--------------------------------------------------------------------------
	return 0;
}
LRESULT MainWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 1;
}
LRESULT MainWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0);
	return 0;
}
LRESULT MainWindow::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CDCHandle dc((HDC)wParam);
	RECT rcClient;
	GetClientRect(&rcClient);
	CBrush bsh;
	bsh.CreateSolidBrush(RGB(64, 224, 225));
	dc.FillRect(&rcClient, bsh);
	return 1;
	// An application should return nonzero if it erases the background; otherwise, it should return zero.
}
LRESULT MainWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//----------------------------------------------------------------------
	if( wParam != SIZE_MINIMIZED ) {
		int w = LOWORD(lParam);
		int h = HIWORD(lParam);
		int x = 10;
		int y = 10;
		m_btnLoadImage.SetWindowPos(NULL, x, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x += (80 + 10);
		m_txtPixel.SetWindowPos(NULL, x, y, 100, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x += (100 + 10);
		m_btnSaveImage.SetWindowPos(NULL, x, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x = 10;
		y += (40 + 10);
		int wi = (w - 10 * 4 - 230) / 2;
		m_imageCtrlOriginal.SetWindowPos(NULL, x, y, wi, h - y - 10, SWP_NOACTIVATE | SWP_NOZORDER);
		m_imageCtrlOriginal.UpdateScroll();
		m_imageCtrlProcess.SetWindowPos(NULL, x + wi + 10, y, wi, h - y - 10, SWP_NOACTIVATE | SWP_NOZORDER);
		m_imageCtrlProcess.UpdateScroll();
		x = w - 10;
		y = 10;
		m_updB.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 20;
		m_editB.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 30;
		m_txtB.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= (20 + 10);
		m_updG.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 20;
		m_editG.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 30;
		m_txtG.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= (20 + 10);
		m_updR.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 20;
		m_editR.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 30;
		m_txtR.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= (20 + 10);
		m_updGray.SetWindowPos(NULL, x - 20, y, 20, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 20;
		m_editGray.SetWindowPos(NULL, x - 30, y, 30, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x -= 30;
		m_txtGray.SetWindowPos(NULL, x - 40, y, 40, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x = w - 10;
		y += (40 + 10);
		m_btnSaveCfg.SetWindowPos(NULL, x - 80, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		m_btnLoadCfg.SetWindowPos(NULL, x - 80 - 10 - 80, y, 80, 40, SWP_NOACTIVATE | SWP_NOZORDER);
		x = 10 + wi + 10 + wi + 10;
		y += (40 + 10);
		m_listLut.SetWindowPos(NULL, x, y, w - 10 - x, h - 10 - y, SWP_NOACTIVATE | SWP_NOZORDER);
	}
	//----------------------------------------------------------------------
	bHandled = FALSE;
	return 1;
}

LRESULT MainWindow::OnBtnLoadImageClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(TRUE);
	if( dlg.DoModal() == IDOK ) {
		CWaitCursor wac;
		m_cmdLoadGray->SetParameter(std::make_any<LPCTSTR>(dlg.m_szFileName));
		m_cmdLoadGray->Exec();
	}
	return 0;
}
LRESULT MainWindow::OnBtnSaveImageClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(FALSE);
	if( dlg.DoModal() == IDOK ) {
		CWaitCursor wac;
		m_cmdSaveColor->SetParameter(std::make_any<LPCTSTR>(dlg.m_szFileName));
		m_cmdSaveColor->Exec();
	}
	return 0;
}

LRESULT MainWindow::OnImageOriginalPixel(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMIMAGEPIXEL* pnm = (NMIMAGEPIXEL*)pNMHDR;
	if( pnm->rgb == CLR_INVALID ) {
		m_txtPixel.SetWindowText(_T(""));
		return 0;
	}
	CString str;
	COLORREF clr = m_imageCtrlProcess.GetImage()->GetPixel(pnm->x, pnm->y);
	str.Format(_T("%u\r\n%u %u %u"),
			(UINT)GetRValue(pnm->rgb),
			(UINT)GetRValue(clr), (UINT)GetGValue(clr), (UINT)GetBValue(clr)
			);
	m_txtPixel.SetWindowText(str);
	return 0;
}

LRESULT MainWindow::OnImageOriginalScroll(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMIMAGESCROLL* pnm = (NMIMAGESCROLL*)pNMHDR;
	m_imageCtrlProcess.SetScrollOffset(pnm->pt);
	return 0;
}
LRESULT MainWindow::OnImageProcessScroll(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMIMAGESCROLL* pnm = (NMIMAGESCROLL*)pNMHDR;
	m_imageCtrlOriginal.SetScrollOffset(pnm->pt);
	return 0;
}

LRESULT MainWindow::OnBtnLoadCfgClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(TRUE);
	if( dlg.DoModal() == IDOK ) {
		CWaitCursor wac;
		USES_CONVERSION;
		std::string str(T2A(dlg.m_szFileName));
		m_cmdLoadCfg->SetParameter(std::make_any<const char*>(str.c_str()));
		m_cmdLoadCfg->Exec();
	}
	return 0;
}
LRESULT MainWindow::OnBtnSaveCfgClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog dlg(FALSE);
	if( dlg.DoModal() == IDOK ) {
		CWaitCursor wac;
		USES_CONVERSION;
		std::string str(T2A(dlg.m_szFileName));
		m_cmdSaveCfg->SetParameter(std::make_any<const char*>(str.c_str()));
		m_cmdSaveCfg->Exec();
	}
	return 0;
}

LRESULT MainWindow::OnListLutClick(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMHDR* pnmh = (NMHDR*)pNMHDR;
	int index = m_listLut.GetSelectedIndex();
	//no selection
	if( index < 0 ) {
		m_editGray.EnableWindow(FALSE);
		m_updGray.EnableWindow(FALSE);
		m_editR.EnableWindow(FALSE);
		m_updR.EnableWindow(FALSE);
		m_editG.EnableWindow(FALSE);
		m_updG.EnableWindow(FALSE);
		m_editB.EnableWindow(FALSE);
		m_updB.EnableWindow(FALSE);
		return 0;
	}
	int gray, r, g, b;
	gray = m_spCfg->GetGrayAt(index);
	m_spCfg->GetRgbAt(index, r, g, b);
	{
		int gray1, gray2;
		if( m_spCfg->GetCount() <= 1 ) {
			gray1 = 0;
			gray2 = 255;
		}
		else {
			if( index == m_spCfg->GetCount() - 1 ) {
				gray1 = m_spCfg->GetGrayAt(index - 1) + 1;
				gray2 = 255;
			}
			else if( index == 0 ) {
				gray1 = 0;
				gray2 = m_spCfg->GetGrayAt(index + 1) - 1;
			}
			else {
				gray1 = m_spCfg->GetGrayAt(index - 1) + 1;
				gray2 = m_spCfg->GetGrayAt(index + 1) - 1;
			}
		}
		m_updGray.SetRange32(gray1, gray2);
	} //end block
	m_updGray.SetPos32(gray);
	m_updR.SetPos32(r);
	m_updG.SetPos32(g);
	m_updB.SetPos32(b);
	//ui
	m_editGray.EnableWindow(TRUE);
	m_updGray.EnableWindow(TRUE);
	m_editR.EnableWindow(TRUE);
	m_updR.EnableWindow(TRUE);
	m_editG.EnableWindow(TRUE);
	m_updG.EnableWindow(TRUE);
	m_editB.EnableWindow(TRUE);
	m_updB.EnableWindow(TRUE);
	return 0;
}

LRESULT MainWindow::OnUpdGrayDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
	int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updGray);
	int index = m_listLut.GetSelectedIndex();
	ATLASSERT( index >= 0 );
	adjust_value_list(v, 0, index);
	int gray = v;
	int r = m_updR.GetPos32();
	int g = m_updG.GetPos32();
	int b = m_updB.GetPos32();
	exec_modify_color_point(index, gray, r, g, b);
	return 0;
}
LRESULT MainWindow::OnUpdRDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
	int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updR);
	int index = m_listLut.GetSelectedIndex();
	ATLASSERT( index >= 0 );
	adjust_value_list(v, 1, index);
	int gray = m_updGray.GetPos32();
	int r = v;
	int g = m_updG.GetPos32();
	int b = m_updB.GetPos32();
	exec_modify_color_point(index, gray, r, g, b);
	return 0;
}
LRESULT MainWindow::OnUpdGDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
	int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updG);
	int index = m_listLut.GetSelectedIndex();
	ATLASSERT( index >= 0 );
	adjust_value_list(v, 2, index);
	int gray = m_updGray.GetPos32();
	int r = m_updR.GetPos32();
	int g = v;
	int b = m_updB.GetPos32();
	exec_modify_color_point(index, gray, r, g, b);
	return 0;
}
LRESULT MainWindow::OnUpdBDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
	NMUPDOWN* pnm = (NMUPDOWN*)pNMHDR;
	int v = calc_upd_value(pnm->iPos + pnm->iDelta, m_updB);
	int index = m_listLut.GetSelectedIndex();
	ATLASSERT( index >= 0 );
	adjust_value_list(v, 3, index);
	int gray = m_updGray.GetPos32();
	int r = m_updR.GetPos32();
	int g = m_updG.GetPos32();
	int b = v;
	exec_modify_color_point(index, gray, r, g, b);
	return 0;
}

int MainWindow::calc_upd_value(int v, CUpDownCtrl& upd)
{
	int iMin, iMax;
	upd.GetRange32(iMin, iMax);
	if( v < iMin )  v = iMin;
	if( v > iMax )  v = iMax;
	return v;
}
void MainWindow::adjust_value_list(int v, int iCol, int index)
{
	ATL::CString str;
	str.Format(_T("%d"), v);
	m_listLut.SetItemText(index, iCol, str);
}
void MainWindow::exec_modify_color_point(int index, int gray, int r, int g, int b)
{
	CWaitCursor wac;
	m_cmdModifyColorPoint->SetParameter(std::make_any<std::tuple<size_t, int, int, int, int>>(
										std::make_tuple((size_t)index, gray, r, g, b)
										));
	m_cmdModifyColorPoint->Exec();
}

//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
