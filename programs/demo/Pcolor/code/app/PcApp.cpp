////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "PcApp.h"

////////////////////////////////////////////////////////////////////////////////

PcApp::PcApp()
{
}

PcApp::~PcApp() throw()
{
}

bool PcApp::Init()
{
	if( m_wndMain.Create(NULL, CWindow::rcDefault, _T("Pseudo Color")) == NULL ) {
		return false;
	}

	//models & view models
	m_spCfgModel = std::make_shared<CfgModel>();
	m_spColorModel = std::make_shared<ColorModel>();
	m_spColorViewModel = std::make_shared<ColorViewModel>();
	m_spColorViewModel->SetCfgModel(m_spCfgModel);
	m_spColorViewModel->SetColorModel(m_spColorModel);

	//binding
	// properties
	m_wndMain.m_imageCtrlOriginal.set_Image(m_spColorViewModel->get_GrayImage());
	m_wndMain.m_imageCtrlProcess.set_Image(m_spColorViewModel->get_ColorImage());
	m_wndMain.set_Cfg(m_spColorViewModel->get_Cfg());
	// commands
	m_wndMain.set_LoadGrayCommand(m_spColorViewModel->get_LoadGrayImageCommand());
	m_wndMain.set_SaveColorCommand(m_spColorViewModel->get_SaveColorImageCommand());
	m_wndMain.set_LoadCfgCommand(m_spColorViewModel->get_LoadCfgCommand());
	m_wndMain.set_SaveCfgCommand(m_spColorViewModel->get_SaveCfgCommand());
	m_wndMain.set_ModifyColorPointCommand(m_spColorViewModel->get_ModifyColorPointCommand());
	// notifications
	m_spCfgModel->AddPropertyNotification(m_spColorViewModel->get_PropertySink());
	m_spColorModel->AddPropertyNotification(m_spColorViewModel->get_PropertySink());
	m_spColorViewModel->AddPropertyNotification(m_wndMain.get_PropertySink());
	m_spColorViewModel->AddCommandNotification(m_wndMain.get_CommandSink());

	return true;
}

void PcApp::Show(int nCmdShow)
{
	m_wndMain.ShowWindow(nCmdShow);
}

////////////////////////////////////////////////////////////////////////////////
