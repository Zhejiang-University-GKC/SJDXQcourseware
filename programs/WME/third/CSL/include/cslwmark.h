/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __CSL_WMARK_H__
#define __CSL_WMARK_H__
////////////////////////////////////////////////////////////////////////////////

#ifndef __CSL_RDP_H__
	#error cslwmark.h requires cslrdp.h to be included first.
#endif

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// Utility

class WmarkUtility
{
public:
	WmarkUtility() throw();
	WmarkUtility(const WmarkUtility&) = delete;
	WmarkUtility& operator=(const WmarkUtility&) = delete;
	~WmarkUtility() throw();

	bool Initialize();

private:
	//actions
	std::shared_ptr<RdScannerAction>  m_spTkAction;
	std::shared_ptr<RdScannerAction>  m_spCommentAction;
	std::shared_ptr<RdScannerAction>  m_spTextAction;

	//table
	std::shared_ptr<RdaTable>  m_spTable;

private:
	friend class WmarkParser;
};

// Parser

class WmarkParser
{
public:
	WmarkParser() throw();
	WmarkParser(const WmarkParser&) = delete;
	WmarkParser& operator=(const WmarkParser&) = delete;
	~WmarkParser() throw();

	void Initialize(uint32_t uMaxErrorNumber, const std::shared_ptr<WmarkUtility>& spU);
	void SetInput(const std::shared_ptr<std::istream>& spStream) throw();
	void SetOutput(const std::shared_ptr<RdMetaData>& spMeta) throw();
	void Start();
	//return value: < 0 (error), = 0 (end), > 0 (succeeded)
	int32_t Parse();
	const std::vector<std::string>& GetErrorArray() const throw();

private:
	std::shared_ptr<WmarkUtility> m_spUtility;
	uint32_t m_uMaxErrorNumber;

	//scanner
	std::shared_ptr<RdScanner> m_spScanner;
	//parser
	RdParser m_parser;

	//data
	RdParserActionMetaData m_data;
};

// Generator

// meta data traversal action
//   [](bool bOpen, RdMetaData& data, RdMetaDataPosition pos, std::ostream& stm)->bool
typedef std::function<bool(bool, RdMetaData&, RdMetaDataPosition, std::ostream&)>  WmarkMetaDataTraversalAction;

class WmarkHtmlGenerator
{
public:
	WmarkHtmlGenerator() noexcept;
	WmarkHtmlGenerator(const WmarkHtmlGenerator&) = delete;
	WmarkHtmlGenerator& operator=(const WmarkHtmlGenerator&) = delete;
	~WmarkHtmlGenerator() noexcept;

	void Initialize();
	bool Generate(RdMetaData& data, std::ostream& stm);

private:
	std::map<uint32_t, WmarkMetaDataTraversalAction>  m_map;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
