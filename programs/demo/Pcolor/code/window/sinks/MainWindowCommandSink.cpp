////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "MainWindowCommandSink.h"

#include "../MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindowCommandSink::MainWindowCommandSink(MainWindow* pW) throw() : m_pW(pW)
{
}

void MainWindowCommandSink::OnCommandComplete(const std::string& str, bool bOK)
{
	if( str == "Load-Gray" ) {
		if( !bOK ) {
			AtlMessageBox(NULL, _T("Cannot load gray image"), _T("error"), MB_OK);
		}
		else {
			//state
			m_pW->m_btnSaveImage.EnableWindow(FALSE);
			m_pW->m_editGray.EnableWindow(FALSE);
			m_pW->m_updGray.EnableWindow(FALSE);
			m_pW->m_editR.EnableWindow(FALSE);
			m_pW->m_updR.EnableWindow(FALSE);
			m_pW->m_editG.EnableWindow(FALSE);
			m_pW->m_updG.EnableWindow(FALSE);
			m_pW->m_editB.EnableWindow(FALSE);
			m_pW->m_updB.EnableWindow(FALSE);
			m_pW->m_btnLoadCfg.EnableWindow(TRUE);
			m_pW->m_btnSaveCfg.EnableWindow(FALSE);
			m_pW->m_listLut.EnableWindow(FALSE);
			m_pW->m_listLut.DeleteAllItems();
		}
	}
	else if( str == "Save-Color" ) {
		if( !bOK ) {
			AtlMessageBox(NULL, _T("Cannot save color image"), _T("error"), MB_OK);
		}
		else {
			m_pW->m_btnSaveImage.EnableWindow(FALSE);
		}
	}
	else if( str == "Load-Cfg" ) {
		if( !bOK ) {
			AtlMessageBox(NULL, _T("Cannot load cfg file"), _T("error"), MB_OK);
		}
		else {
			m_pW->m_editGray.EnableWindow(FALSE);
			m_pW->m_updGray.EnableWindow(FALSE);
			m_pW->m_editR.EnableWindow(FALSE);
			m_pW->m_updR.EnableWindow(FALSE);
			m_pW->m_editG.EnableWindow(FALSE);
			m_pW->m_updG.EnableWindow(FALSE);
			m_pW->m_editB.EnableWindow(FALSE);
			m_pW->m_updB.EnableWindow(FALSE);
			m_pW->m_btnSaveCfg.EnableWindow(FALSE);
			m_pW->m_listLut.EnableWindow(TRUE);
			m_pW->m_listLut.DeleteAllItems();
			ATL::CString str;
			for( size_t i = 0; i < m_pW->m_spCfg->GetCount(); i ++ ) {
				int r, g, b;
				m_pW->m_spCfg->GetRgbAt(i, r, g, b);
				m_pW->m_listLut.InsertItem((int)i, _T(""));
				str.Format(_T("%d"), m_pW->m_spCfg->GetGrayAt(i));
				m_pW->m_listLut.SetItemText((int)i, 0, str);
				str.Format(_T("%d"), r);
				m_pW->m_listLut.SetItemText((int)i, 1, str);
				str.Format(_T("%d"), g);
				m_pW->m_listLut.SetItemText((int)i, 2, str);
				str.Format(_T("%d"), b);
				m_pW->m_listLut.SetItemText((int)i, 3, str);
			}
			m_pW->m_btnSaveImage.EnableWindow(TRUE);
		}
	}
	else if( str == "Save-Cfg" ) {
		if( !bOK ) {
			AtlMessageBox(NULL, _T("Cannot save cfg file"), _T("error"), MB_OK);
		}
		else {
			m_pW->m_btnSaveCfg.EnableWindow(FALSE);
		}
	}
	else if( str == "Modify-Color-Point" ) {
		if( !bOK ) {
			AtlMessageBox(NULL, _T("Cannot modify color point"), _T("error"), MB_OK);
		}
		else {
			m_pW->m_btnSaveCfg.EnableWindow(TRUE);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
