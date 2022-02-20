////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "ColorModel.h"

#include "alg/PcAlg.h"

////////////////////////////////////////////////////////////////////////////////

// ColorModel

ColorModel::ColorModel() noexcept
{
}
ColorModel::~ColorModel() noexcept
{
}

const GrayData& ColorModel::GetGrayData() const noexcept
{
	return m_gData;
}
const ColorData& ColorModel::GetColorData() const noexcept
{
	return m_cData;
}

bool ColorModel::LoadGrayImage(LPCTSTR szFile)
{
	ATL::CImage image;
	if( FAILED(image.Load(szFile)) )
		return false;
	int iBPP = image.GetBPP();
	if( iBPP != 8 && iBPP != 24 )
		return false;
	ImageDataHelper::ImageToColorData(image, m_cData);
	ImageDataHelper::ColorDataToGrayData(m_cData, m_gData);
	Fire_OnPropertyChanged("gray_data");
	Fire_OnPropertyChanged("color_data");
	return true;
}

bool ColorModel::SaveColorImage(LPCTSTR szFile)
{
	ATL::CImage image;
	ImageDataHelper::ColorDataToImage(m_cData, image);
	return SUCCEEDED(image.Save(szFile, Gdiplus::ImageFormatBMP));
}

void ColorModel::Colorize(const PcCfg& cfg)
{
	PcAlgHelper::PseudoColor(m_gData, cfg, m_cData);
	Fire_OnPropertyChanged("color_data");
}

////////////////////////////////////////////////////////////////////////////////
