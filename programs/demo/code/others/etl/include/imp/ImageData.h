////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////
//灰度数组

class GrayData
{
public:
	GrayData() throw() : m_iW(0), m_iH(0)
	{
	}
	~GrayData() throw()
	{
	}

	void Clear() throw()
	{
		m_buffer.clear();
		m_iW = m_iH = 0;
	}

	bool IsNull() const throw()
	{
		return m_buffer.empty();
	}

	uchar* GetAddress() throw()
	{
		return m_buffer.data();
	}
	const uchar* GetAddress() const throw()
	{
		return m_buffer.data();
	}
	int GetWidth() const throw()
	{
		return m_iW;
	}
	int GetHeight() const throw()
	{
		return m_iH;
	}

	void Allocate(int iW, int iH)
	{
		assert( iW > 0 && iH > 0 );
		Clear();
		m_buffer.resize(iW * iH);  //overflow?
		m_iW = iW;
		m_iH = iH;
	}

	//copy
	void CopyTo(GrayData& dest)
	{
		if( IsNull() ) {
			dest.Clear();
			return ;
		}
		dest.Allocate(m_iW, m_iH);
		::memcpy(dest.GetAddress(), GetAddress(), m_iW * m_iH * sizeof(uchar));
	}

private:
	std::vector<uchar> m_buffer;  //gray array
	int m_iW, m_iH;//宽度、高度

private:
	GrayData(const GrayData&) throw();
	GrayData& operator=(const GrayData&) throw();
};

class ColorData
{
public:
	ColorData() throw() : m_iW(0), m_iH(0)
	{
	}
	~ColorData() throw()
	{
	}

	void Clear() throw()
	{
		m_spR.clear();
		m_spG.clear();
		m_spB.clear();
		m_iW = m_iH = 0;
	}

	bool IsNull() const throw()
	{
		return m_spR.empty() || m_spG.empty() || m_spB.empty();
	}

	uchar* GetAddressR() throw()
	{
		return m_spR.data();
	}
	const uchar* GetAddressR() const throw()
	{
		return m_spR.data();
	}
	uchar* GetAddressG() throw()
	{
		return m_spG.data();
	}
	const uchar* GetAddressG() const throw()
	{
		return m_spG.data();
	}
	uchar* GetAddressB() throw()
	{
		return m_spB.data();
	}
	const uchar* GetAddressB() const throw()
	{
		return m_spB.data();
	}
	
	int GetWidth() const throw()
	{
		return m_iW;
	}
	int GetHeight() const throw()
	{
		return m_iH;
	}

	void Allocate(int iW, int iH)
	{
		assert( iW > 0 && iH > 0 );
		Clear();
		m_spR.resize(iW * iH);
		m_spG.resize(iW * iH);
		m_spB.resize(iW * iH);
		m_iW = iW;
		m_iH = iH;
	}

	//copy
	void CopyTo(ColorData& dest)
	{
		if( IsNull() ) {
			dest.Clear();
			return ;
		}
		dest.Allocate(m_iW, m_iH);
		::memcpy(dest.GetAddressR(), GetAddressR(), m_iW * m_iH * sizeof(uchar));
		::memcpy(dest.GetAddressG(), GetAddressG(), m_iW * m_iH * sizeof(uchar));
		::memcpy(dest.GetAddressB(), GetAddressB(), m_iW * m_iH * sizeof(uchar));
	}

private:
	std::vector<uchar> m_spR;
	std::vector<uchar> m_spG;
	std::vector<uchar> m_spB;
	int m_iW, m_iH;

private:
	ColorData(const ColorData&) throw();
	ColorData& operator=(const ColorData&) throw();
};

// ImageDataHelper

class ImageDataHelper
{
public:
	//CImage->ColorData
	static void ImageToColorData(const CImage& image, ColorData& data)
	{
		data.Clear();
		if( image.IsNull() )
			return ;

		int iBPP = image.GetBPP();//得到单位像素的位数
		assert( iBPP == 8 || iBPP == 24 );  //必须是灰度图或彩色图才转换
		int iW = image.GetWidth();
		int iH = image.GetHeight();
		data.Allocate(iW, iH);  //may throw

		RGBQUAD table[256];//结构数组,调色板，彩色图没有调色板
		if( iBPP == 8 )
			image.GetColorTable(0, 256, table);//得到图像的RGB信息

		BYTE* ps = (BYTE*)image.GetBits();//返回图像数据buffer指针
		uchar* pdR = data.GetAddressR();
		uchar* pdG = data.GetAddressG();
		uchar* pdB = data.GetAddressB();

		for( int i = 0; i < iH; i ++ ) {
			BYTE* psr = ps;
			for( int j = 0; j < iW; j ++ ) {
				if( iBPP == 8 ) {//8位灰度图,每一字节是一个像素灰度级
					BYTE v = *psr ++;
					*pdR ++ = table[v].rgbRed;
					*pdG ++ = table[v].rgbGreen;
					*pdB ++ = table[v].rgbBlue;
				}
				else {//24位彩色,每三字节是一个像素RGB(存储顺序是BGR)
					*pdB ++ = *psr ++;
					*pdG ++ = *psr ++;
					*pdR ++ = *psr ++;
				}
			}
			ps += image.GetPitch();
		} //end for
	}
	//ColorData->CImage
	static void ColorDataToImage(const ColorData& data, CImage& image)
	{
		if( data.IsNull() )
			return ;
		int iW = data.GetWidth();
		int iH = data.GetHeight();
		{
			ATL::CImage imgCvt;
			if( !imgCvt.Create(iW, iH, 24) )
				return ;
			image.Destroy();
			image.Attach(imgCvt.Detach());
		} //end block

		const uchar* psR = data.GetAddressR();
		const uchar* psG = data.GetAddressG();
		const uchar* psB = data.GetAddressB();
		BYTE* pd = (BYTE*)image.GetBits();
		for( int i = 0; i < iH; i ++ ) {
			BYTE* pdr = pd;
			for( int j = 0; j < iW; j ++ ) {
				*pdr ++ = *psB ++;
				*pdr ++ = *psG ++;
				*pdr ++ = *psR ++;
			}
			pd += image.GetPitch();
		} //end for
	}
	//GrayData->CImage
	static void GrayDataToImage(const GrayData& data, CImage& image)
	{
		if( data.IsNull() )
			return ;
		int iW = data.GetWidth();
		int iH = data.GetHeight();
		{
			ATL::CImage imgCvt;
			if( !imgCvt.Create(iW, iH, 8) )
				return ;
			image.Destroy();
			image.Attach(imgCvt.Detach());
		} //end block

		RGBQUAD table[256];
		for( int i = 0; i < 256; i ++ ) {
			table[i].rgbRed = i;
			table[i].rgbGreen = i;
			table[i].rgbBlue = i;
			table[i].rgbReserved = 0;
		}
		image.SetColorTable(0, 256, table);

		const uchar* ps = data.GetAddress();
		BYTE* pd = (BYTE*)image.GetBits();
		for( int i = 0; i < iH; i ++ ) {
			BYTE* pdr = pd;
			for( int j = 0; j < iW; j ++ ) {
				*pdr ++ = *ps ++;
			}
			pd += image.GetPitch();
		} //end for
	}
	//ColorData->GrayData
	static void ColorDataToGrayData(const ColorData& cData, GrayData& gData)
	{
		gData.Clear();
		if( cData.IsNull() )
			return ;

		int height = cData.GetHeight();
		int width = cData.GetWidth();
		gData.Allocate(width, height);

		const uchar* psR = cData.GetAddressR();
		const uchar* psG = cData.GetAddressG();
		const uchar* psB = cData.GetAddressB();
		uchar* pd  = gData.GetAddress();

		for( int i = 0; i < height; i ++ ) {
			for( int j = 0; j < width; j ++ ) {
				double dR = (double)(*psR ++);
				double dG = (double)(*psG ++);
				double dB = (double)(*psB ++);
				double v = 0.11 * dR + 0.59 * dG + 0.3 * dB;
				*pd ++ = (uchar)((v > 255.0) ? 255.0 : ((v < 0.0) ? 0.0 : v));
			}
		}
	}

	static void Invert(GrayData& gData) throw()
	{
		uchar* pd = gData.GetAddress();
		int iW = gData.GetWidth();
		int iH = gData.GetHeight();
		for( int i = 0; i < iH; i ++ ) {
			for( int j = 0; j < iW; j ++ ) {
				*pd = 255 - *pd;
				pd ++;
			}
		}
	}
	static void BoolInvert(GrayData& gData) throw()
	{
		uchar* pd = gData.GetAddress();
		int iW = gData.GetWidth();
		int iH = gData.GetHeight();
		for( int i = 0; i < iH; i ++ ) {
			for( int j = 0; j < iW; j ++ ) {
				if( *pd != 0 )
					*pd = 0;
				else
					*pd = 255;
				pd ++;
			}
		}
	}
	//然后对于大于阈值的pixel重新处理，将灰度图变为二值图
	static void ToBinary(int iThreshold, GrayData& gData) throw()
	{
		uchar* pd = gData.GetAddress();
		int height = gData.GetHeight();
		int width = gData.GetWidth();

		for( int i = 0; i < height; i ++ ) {
			for( int j = 0; j < width; j ++ ) {
				int temp = (int)(*pd);

				if( temp >= iThreshold )
					*pd = (uchar)255;
				else
					*pd = (uchar)0;
				pd++;
			}
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
