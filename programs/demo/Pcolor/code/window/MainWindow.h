////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "ui/ImageCtrl.h"

#include "../common/PcCfg.h"

#include "sinks/MainWindowPropertySink.h"
#include "sinks/MainWindowCommandSink.h"

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public CWindowImpl<MainWindow, CWindow, CFrameWinTraits>
{
public:
	DECLARE_WND_CLASS(_T("Pcolor Window Class"))

	//--------------------------------------------------------------------------
	enum { IDC_BTN_LOAD_IMAGE = 10,
		IDC_TEXT_PIXEL,
		IDC_BTN_SAVE_IMAGE,
		IDC_PIC_ORIGINAL,
		IDC_PIC_PROCESS,
		IDC_TEXT_GRAY,
		IDC_EDIT_GRAY,
		IDC_UPDOWN_GRAY,
		IDC_TEXT_R,
		IDC_EDIT_R,
		IDC_UPDOWN_R,
		IDC_TEXT_G,
		IDC_EDIT_G,
		IDC_UPDOWN_G,
		IDC_TEXT_B,
		IDC_EDIT_B,
		IDC_UPDOWN_B,
		IDC_BTN_LOAD_CFG,
		IDC_BTN_SAVE_CFG,
		IDC_LIST_LUT
	};

	CButton	       m_btnLoadImage;
	CStatic        m_txtPixel;
	CButton	       m_btnSaveImage;
	ImageCtrl      m_imageCtrlOriginal;
	ImageCtrl      m_imageCtrlProcess;
	CStatic        m_txtGray;
	CEdit          m_editGray;
	CUpDownCtrl    m_updGray;
	CStatic        m_txtR;
	CEdit          m_editR;
	CUpDownCtrl    m_updR;
	CStatic        m_txtG;
	CEdit          m_editG;
	CUpDownCtrl    m_updG;
	CStatic        m_txtB;
	CEdit          m_editB;
	CUpDownCtrl    m_updB;
	CButton        m_btnLoadCfg;
	CButton        m_btnSaveCfg;
	CListViewCtrl  m_listLut;
	//--------------------------------------------------------------------------

	MainWindow();

	//--------------------------------------------------------------------------
public:
	//properties
	void set_Cfg(const std::shared_ptr<PcCfg>& sp) noexcept;

	//commands
	void set_LoadGrayCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept;
	void set_SaveColorCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept;
	void set_LoadCfgCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept;
	void set_SaveCfgCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept;
	void set_ModifyColorPointCommand(const std::shared_ptr<ICommandBase>& cmd) noexcept;

	//notifications
	std::shared_ptr<IPropertyNotification> get_PropertySink() noexcept;
	std::shared_ptr<ICommandNotification> get_CommandSink() noexcept;

private:
	//properties
	std::shared_ptr<PcCfg> m_spCfg;

	//commands
	std::shared_ptr<ICommandBase> m_cmdLoadGray;
	std::shared_ptr<ICommandBase> m_cmdSaveColor;
	std::shared_ptr<ICommandBase> m_cmdLoadCfg;
	std::shared_ptr<ICommandBase> m_cmdSaveCfg;
	std::shared_ptr<ICommandBase> m_cmdModifyColorPoint;

	//notifications
	std::shared_ptr<MainWindowPropertySink> m_spPropertySink;
	std::shared_ptr<MainWindowCommandSink>  m_spCommandSink;

private:
	friend class MainWindowPropertySink;
	friend class MainWindowCommandSink;
	//--------------------------------------------------------------------------

public:
//message handler
	BEGIN_MSG_MAP(MainWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)  // Sent when the window background must be erased (for example, when a window is resized).
		MESSAGE_HANDLER(WM_SIZE, OnSize)
//------------------------------------------------------------------------------
		COMMAND_HANDLER(IDC_BTN_LOAD_IMAGE, BN_CLICKED, OnBtnLoadImageClicked)
		COMMAND_HANDLER(IDC_BTN_SAVE_IMAGE, BN_CLICKED, OnBtnSaveImageClicked)
		NOTIFY_HANDLER(IDC_PIC_ORIGINAL, ICN_PIXEL, OnImageOriginalPixel)
		NOTIFY_HANDLER(IDC_PIC_ORIGINAL, ICN_SCROLL, OnImageOriginalScroll)
		NOTIFY_HANDLER(IDC_PIC_PROCESS, ICN_SCROLL, OnImageProcessScroll)
		COMMAND_HANDLER(IDC_BTN_LOAD_CFG, BN_CLICKED, OnBtnLoadCfgClicked)
		COMMAND_HANDLER(IDC_BTN_SAVE_CFG, BN_CLICKED, OnBtnSaveCfgClicked)
		NOTIFY_HANDLER(IDC_LIST_LUT, NM_CLICK, OnListLutClick)
		NOTIFY_HANDLER(IDC_UPDOWN_GRAY, UDN_DELTAPOS, OnUpdGrayDelta)
		NOTIFY_HANDLER(IDC_UPDOWN_R, UDN_DELTAPOS, OnUpdRDelta)
		NOTIFY_HANDLER(IDC_UPDOWN_G, UDN_DELTAPOS, OnUpdGDelta)
		NOTIFY_HANDLER(IDC_UPDOWN_B, UDN_DELTAPOS, OnUpdBDelta)
//------------------------------------------------------------------------------
		REFLECT_NOTIFICATIONS()
//------------------------------------------------------------------------------
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//--------------------------------------------------------------------------
	LRESULT OnBtnLoadImageClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBtnSaveImageClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnImageOriginalPixel(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnImageOriginalScroll(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnImageProcessScroll(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnBtnLoadCfgClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBtnSaveCfgClicked(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnListLutClick(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnUpdGrayDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnUpdRDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnUpdGDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);
	LRESULT OnUpdBDelta(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled);

private:
	int calc_upd_value(int v, CUpDownCtrl& upd);
	void adjust_value_list(int v, int iCol, int index);
	void exec_modify_color_point(int index, int gray, int r, int g, int b);
	//--------------------------------------------------------------------------
};

////////////////////////////////////////////////////////////////////////////////
