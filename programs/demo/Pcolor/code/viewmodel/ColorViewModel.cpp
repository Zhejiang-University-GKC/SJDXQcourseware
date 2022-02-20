////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "ColorViewModel.h"

////////////////////////////////////////////////////////////////////////////////

// ColorViewModel

ColorViewModel::ColorViewModel() : m_spGrayImage(std::make_shared<ATL::CImage>()),
								m_spColorImage(std::make_shared<ATL::CImage>()),
								m_cmdLoadGrayImage(std::make_shared<LoadGrayImageCommand>(this)),
								m_cmdSaveColorImage(std::make_shared<SaveColorImageCommand>(this)),
								m_cmdLoadCfg(std::make_shared<LoadCfgCommand>(this)),
								m_cmdSaveCfg(std::make_shared<SaveCfgCommand>(this)),
								m_cmdModifyColorPoint(std::make_shared<ModifyColorPointCommand>(this)),
								m_spSink(std::make_shared<ColorViewModelSink>(this))
{
}
ColorViewModel::~ColorViewModel() noexcept
{
}

void ColorViewModel::SetColorModel(const std::shared_ptr<ColorModel>& model) noexcept
{
	m_spColorModel = model;
}
void ColorViewModel::SetCfgModel(const std::shared_ptr<CfgModel>& model) noexcept
{
	m_spCfgModel = model;
}

//properties

std::shared_ptr<ATL::CImage> ColorViewModel::get_GrayImage() noexcept
{
	return m_spGrayImage;
}
std::shared_ptr<ATL::CImage> ColorViewModel::get_ColorImage() noexcept
{
	return m_spColorImage;
}
std::shared_ptr<PcCfg> ColorViewModel::get_Cfg() noexcept
{
	return m_spCfgModel->GetCfg();
}

//commands

std::shared_ptr<ICommandBase> ColorViewModel::get_LoadGrayImageCommand() noexcept
{
	return std::static_pointer_cast<ICommandBase>(m_cmdLoadGrayImage);
}
std::shared_ptr<ICommandBase> ColorViewModel::get_SaveColorImageCommand() noexcept
{
	return std::static_pointer_cast<ICommandBase>(m_cmdSaveColorImage);
}
std::shared_ptr<ICommandBase> ColorViewModel::get_LoadCfgCommand() noexcept
{
	return std::static_pointer_cast<ICommandBase>(m_cmdLoadCfg);
}
std::shared_ptr<ICommandBase> ColorViewModel::get_SaveCfgCommand() noexcept
{
	return std::static_pointer_cast<ICommandBase>(m_cmdSaveCfg);
}
std::shared_ptr<ICommandBase> ColorViewModel::get_ModifyColorPointCommand() noexcept
{
	return std::static_pointer_cast<ICommandBase>(m_cmdModifyColorPoint);
}

//notifications

std::shared_ptr<IPropertyNotification> ColorViewModel::get_PropertySink() noexcept
{
	return std::static_pointer_cast<IPropertyNotification>(m_spSink);
}

////////////////////////////////////////////////////////////////////////////////
