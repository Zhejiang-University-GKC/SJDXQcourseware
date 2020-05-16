/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __TEXT_DEF_H__
#define __TEXT_DEF_H__
////////////////////////////////////////////////////////////////////////////////

//property IDs

enum {
	PROPID_TEXT = 2,
	PROPID_BACK_COLOR
};

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// RgbColor

class RgbColor
{
public:
	RgbColor() noexcept : m_r(0), m_g(0), m_b(0) {}
	RgbColor(uchar r, uchar g, uchar b) noexcept : m_r(r), m_g(g), m_b(b) {}
	RgbColor(const RgbColor& src) noexcept : m_r(src.m_r), m_g(src.m_g), m_b(src.m_b) {}
	~RgbColor() noexcept {}

	RgbColor& operator=(const RgbColor& src) noexcept
	{ m_r = src.m_r; m_g = src.m_g; m_b = src.m_b; return *this; }

	bool operator==(const RgbColor& rhs) const noexcept
	{ return m_r == rhs.m_r && m_g == rhs.m_g && m_b == rhs.m_b; }
	bool operator!=(const RgbColor& rhs) const noexcept
	{ return m_r != rhs.m_r || m_g != rhs.m_g || m_b != rhs.m_b; }

	uchar r() const noexcept { return m_r; }
	uchar g() const noexcept { return m_g; }
	uchar b() const noexcept { return m_b; }

	void Set(uchar r, uchar g, uchar b) noexcept
	{ m_r = r; m_g = g; m_b = b; }

private:
	uchar m_r, m_g, m_b;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
