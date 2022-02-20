////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "MainWindowPropertySink.h"

#include "../MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

MainWindowPropertySink::MainWindowPropertySink(MainWindow* pW) throw() : m_pW(pW)
{
}

void MainWindowPropertySink::OnPropertyChanged(const std::string& str)
{
	if( str == "gray_data" ) {
		m_pW->m_imageCtrlOriginal.UpdateScroll();
	}
	else if( str == "color_data" ) {
		m_pW->m_imageCtrlProcess.UpdateScroll();
	}
}

////////////////////////////////////////////////////////////////////////////////
