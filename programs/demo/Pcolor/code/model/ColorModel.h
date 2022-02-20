////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "imp/ImageData.h"

#include "../common/PcCfg.h"

////////////////////////////////////////////////////////////////////////////////

// ColorModel

class ColorModel : public Proxy_PropertyNotification<ColorModel>
{
public:
	ColorModel() noexcept;
	ColorModel(const ColorModel&) = delete;
	ColorModel& operator=(const ColorModel&) = delete;
	~ColorModel() noexcept;

	const GrayData& GetGrayData() const noexcept;
	const ColorData& GetColorData() const noexcept;

	bool LoadGrayImage(LPCTSTR szFile);
	bool SaveColorImage(LPCTSTR szFile);

	void Colorize(const PcCfg& cfg);

private:
	GrayData  m_gData;
	ColorData m_cData;
};

////////////////////////////////////////////////////////////////////////////////
