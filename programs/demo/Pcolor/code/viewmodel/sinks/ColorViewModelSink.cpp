////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "ColorViewModelSink.h"

#include "../ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

ColorViewModelSink::ColorViewModelSink(ColorViewModel* p) throw() : m_pVM(p)
{
}

void ColorViewModelSink::OnPropertyChanged(const std::string& str)
{
	if( str == "gray_data" ) {
		ImageDataHelper::GrayDataToImage(m_pVM->m_spColorModel->GetGrayData(), *(m_pVM->m_spGrayImage));
		m_pVM->Fire_OnPropertyChanged(str);
	}
	else if( str == "color_data" ) {
		ImageDataHelper::ColorDataToImage(m_pVM->m_spColorModel->GetColorData(), *(m_pVM->m_spColorImage));
		m_pVM->Fire_OnPropertyChanged(str);
	}
	else if( str == "Cfg" ) {
		m_pVM->m_spColorModel->Colorize(*(m_pVM->m_spCfgModel->GetCfg()));
	}
}

////////////////////////////////////////////////////////////////////////////////
