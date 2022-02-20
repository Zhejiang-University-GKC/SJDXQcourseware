////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "imp/ImageData.h"

#include "../../common/PcCfg.h"

////////////////////////////////////////////////////////////////////////////////

class PcAlgHelper
{
public:
	static void PseudoColor(const GrayData& gData, const PcCfg& cfg, ColorData& cData) throw()
	{
		int iW = gData.GetWidth();
		int iH = gData.GetHeight();
		const uchar* ps = gData.GetAddress();
		uchar* pR = cData.GetAddressR();
		uchar* pG = cData.GetAddressG();
		uchar* pB = cData.GetAddressB();
		int r, g, b;
		for( int i = 0; i < iW * iH; i ++ ) {
			calc_color_value(*ps ++, cfg, r, g, b);
			*pR ++ = (uchar)r;
			*pG ++ = (uchar)g;
			*pB ++ = (uchar)b;
		}
	}

private:
	static void calc_color_value(int gray, const PcCfg& cfg, int& r, int& g, int& b) throw()
	{
		if ( cfg.GetCount() == 0 ) {
			r = g = b = gray;
			return ;
		}
		//find
		size_t index = 0;
		for( ; index < cfg.GetCount(); index ++ ) {
			if( gray <= cfg.GetGrayAt(index) )
				break;
		}
		//borders
		int gray1, gray2;
		int r1, r2;
		int g1, g2;
		int b1, b2;
		if( index == cfg.GetCount() ) {
			gray1 = cfg.GetGrayAt(index - 1);
			cfg.GetRgbAt(index - 1, r1, g1, b1);
			gray2 = r2 = g2 = b2 = 255;
		}
		else {
			gray2 = cfg.GetGrayAt(index);
			cfg.GetRgbAt(index, r2, g2, b2);
			if( index == 0 ) {
				gray1 = r1 = g1 = b1 = 0;
			}
			else {
				gray1 = cfg.GetGrayAt(index - 1);
				cfg.GetRgbAt(index - 1, r1, g1, b1);
			}
		}
		if( gray1 == gray2 ) {
			r = r2;
			g = g2;
			b = b2;
			return ;
		}
		double k = (double)(gray - gray1) / (double)(gray2 - gray1);
		r = (int)(k * (double)(r2 - r1) + (double)r1 + 0.5);
		if( r < 0 )    r = 0;
		if( r > 255 )  r = 255;
		g = (int)(k * (double)(g2 - g1) + (double)g1 + 0.5);
		if( g < 0 )    g = 0;
		if( g > 255 )  g = 255;
		b = (int)(k * (double)(b2 - b1) + (double)b1 + 0.5);
		if( b < 0 )    b = 0;
		if( b > 255 )  b = 255;
	}
};

////////////////////////////////////////////////////////////////////////////////
