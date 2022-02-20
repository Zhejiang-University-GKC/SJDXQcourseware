////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include <fstream>
#include <sstream>

#include "PcCfg.h"

////////////////////////////////////////////////////////////////////////////////

// PcCfg

bool PcCfg::Load(const char* szFile)
{
	clear();

	std::ifstream fin(szFile, std::ios::in);
	if( !fin.is_open() )
		return false;
	std::string strLine;
	while( std::getline(fin, strLine) ) {
		if( strLine.length() != 0 ) {
			std::stringstream st(strLine, std::ios::in);
			int v;
			st >> v;
			m_vecGray.push_back(v);
			st >> v;
			m_vecR.push_back(v);
			st >> v;
			m_vecG.push_back(v);
			st >> v;
			m_vecB.push_back(v);
		}
	}
	fin.close();

	if( m_vecGray.size() == 0 )
		return false;
	//check
	for( size_t i = 0; i < m_vecGray.size(); i ++ ) {
		if( m_vecGray[i] < 0 || m_vecGray[i] > 255 )
			return false;
		if( m_vecR[i] < 0 || m_vecR[i] > 255 )
			return false;
		if( m_vecG[i] < 0 || m_vecG[i] > 255 )
			return false;
		if( m_vecB[i] < 0 || m_vecB[i] > 255 )
			return false;
		if( i != m_vecGray.size() - 1 ) {
			if( m_vecGray[i] >= m_vecGray[i + 1] )
				return false;
		}
	}

	return true;
}

bool PcCfg::Save(const char* szFile)
{
	std::ofstream fout(szFile, std::ios::out | std::ios::trunc);
	if( !fout.is_open() )
		return false;
	for( size_t i = 0; i < m_vecGray.size(); i ++ ) {
		fout << m_vecGray[i];
		fout << " ";
		fout << m_vecR[i];
		fout << " ";
		fout << m_vecG[i];
		fout << " ";
		fout << m_vecB[i];
		fout << std::endl;
	}
	fout.close();
	return true;
}

////////////////////////////////////////////////////////////////////////////////
