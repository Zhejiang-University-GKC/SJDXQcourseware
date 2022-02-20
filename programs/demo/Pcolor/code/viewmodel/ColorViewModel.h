////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "../model/ColorModel.h"
#include "../model/CfgModel.h"

#include "commands/LoadGrayImageCommand.h"
#include "commands/SaveColorImageCommand.h"
#include "commands/LoadCfgCommand.h"
#include "commands/SaveCfgCommand.h"
#include "commands/ModifyColorPointCommand.h"

#include "sinks/ColorViewModelSink.h"

////////////////////////////////////////////////////////////////////////////////

// ColorViewModel

class ColorViewModel : public Proxy_PropertyNotification<ColorViewModel>,
					public Proxy_CommandNotification<ColorViewModel>
{
public:
	ColorViewModel();
	ColorViewModel(const ColorViewModel&) = delete;
	ColorViewModel& operator=(const ColorViewModel&) = delete;
	~ColorViewModel() noexcept;

	void SetColorModel(const std::shared_ptr<ColorModel>& model) noexcept;
	void SetCfgModel(const std::shared_ptr<CfgModel>& model) noexcept;

//properties
	std::shared_ptr<ATL::CImage> get_GrayImage() noexcept;
	std::shared_ptr<ATL::CImage> get_ColorImage() noexcept;
	std::shared_ptr<PcCfg> get_Cfg() noexcept;

//commands
	std::shared_ptr<ICommandBase> get_LoadGrayImageCommand() noexcept;
	std::shared_ptr<ICommandBase> get_SaveColorImageCommand() noexcept;
	std::shared_ptr<ICommandBase> get_LoadCfgCommand() noexcept;
	std::shared_ptr<ICommandBase> get_SaveCfgCommand() noexcept;
	std::shared_ptr<ICommandBase> get_ModifyColorPointCommand() noexcept;

//notifications
	std::shared_ptr<IPropertyNotification> get_PropertySink() noexcept;

private:
	std::shared_ptr<ColorModel> m_spColorModel;
	std::shared_ptr<CfgModel> m_spCfgModel;

	std::shared_ptr<ATL::CImage> m_spGrayImage;
	std::shared_ptr<ATL::CImage> m_spColorImage;

	std::shared_ptr<LoadGrayImageCommand> m_cmdLoadGrayImage;
	std::shared_ptr<SaveColorImageCommand> m_cmdSaveColorImage;
	std::shared_ptr<LoadCfgCommand> m_cmdLoadCfg;
	std::shared_ptr<SaveCfgCommand> m_cmdSaveCfg;
	std::shared_ptr<ModifyColorPointCommand> m_cmdModifyColorPoint;

	std::shared_ptr<ColorViewModelSink> m_spSink;

private:
	friend class LoadGrayImageCommand;
	friend class SaveColorImageCommand;
	friend class LoadCfgCommand;
	friend class SaveCfgCommand;
	friend class ModifyColorPointCommand;
	friend class ColorViewModelSink;
};

////////////////////////////////////////////////////////////////////////////////
