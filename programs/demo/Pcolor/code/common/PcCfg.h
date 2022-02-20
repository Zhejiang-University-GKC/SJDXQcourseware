////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

// PcCfg

class PcCfg
{
public:
	PcCfg() throw()
	{
	}
	PcCfg(PcCfg&& src) : m_vecGray(std::move(src.m_vecGray)),
						m_vecR(std::move(src.m_vecR)),
						m_vecG(std::move(src.m_vecG)),
						m_vecB(std::move(src.m_vecB))
	{
	}
	~PcCfg() throw()
	{
	}

	PcCfg& operator=(PcCfg&& src) throw()
	{
		m_vecGray = std::move(src.m_vecGray);
		m_vecR = std::move(src.m_vecR);
		m_vecG = std::move(src.m_vecG);
		m_vecB = std::move(src.m_vecB);
		return *this;
	}

	size_t GetCount() const throw()
	{
		return m_vecGray.size();
	}
	int GetGrayAt(size_t index) const throw()
	{
		assert( index < GetCount() );
		return m_vecGray[index];
	}
	void GetRgbAt(size_t index, int& r, int& g, int& b) const throw()
	{
		assert( index < GetCount() );
		r = m_vecR[index];
		g = m_vecG[index];
		b = m_vecB[index];
	}
	void SetGrayAt(size_t index, int gray) throw()
	{
		assert( index < GetCount() );
		m_vecGray[index] = gray;
	}
	void SetRAt(size_t index, int r) throw()
	{
		assert( index < GetCount() );
		m_vecR[index] = r;
	}
	void SetGAt(size_t index, int g) throw()
	{
		assert( index < GetCount() );
		m_vecG[index] = g;
	}
	void SetBAt(size_t index, int b) throw()
	{
		assert( index < GetCount() );
		m_vecB[index] = b;
	}

	bool Load(const char* szFile);
	bool Save(const char* szFile);

private:
	void clear() throw()
	{
		m_vecGray.clear();
		m_vecR.clear();
		m_vecG.clear();
		m_vecB.clear();
	}

private:
	std::vector<int> m_vecGray;
	std::vector<int> m_vecR;
	std::vector<int> m_vecG;
	std::vector<int> m_vecB;

private:
	PcCfg(const PcCfg&) throw();
	PcCfg& operator=(const PcCfg&) throw();
};

////////////////////////////////////////////////////////////////////////////////
