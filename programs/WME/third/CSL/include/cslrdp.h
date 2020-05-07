/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __CSL_RDP_H__
#define __CSL_RDP_H__
////////////////////////////////////////////////////////////////////////////////

#ifndef __CSL_BASE_H__
	#error cslrdp.h requires cslbase.h to be included first.
#endif

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// Recursive descent parser (LL1)

// right-linear grammar

//tokens
#define TK_EPSILON       ((uint32_t)-10)
#define TK_NULL          (0)
#define TK_ERROR         ((uint32_t)-1)
#define TK_END_OF_EVENT  ((uint32_t)-2)
#define TK_START         (1)

#define TK_NO_EVENT      ((uint32_t)-3)

// RdCharInfo
struct RdCharInfo
{
	uint32_t uRow;
	uint32_t uCol;
};

// RdToken
struct RdToken
{
	std::string strToken;
	uint32_t uID;
	RdCharInfo infoStart;
	RdCharInfo infoEnd;
};

// action stack
typedef std::stack<uint32_t>  RdActionStack;

// scanner action
//   [](std::istream& stm, RdActionStack& stk, RdToken& token)->bool
typedef std::function<bool(std::istream&, RdActionStack&, RdToken&)>  RdScannerAction;

// RdScanner
class RdScanner
{
public:
	RdScanner() throw();
	RdScanner(const RdScanner&) = delete;
	RdScanner& operator=(const RdScanner&) = delete;
	~RdScanner() throw();

	void SetStream(const std::shared_ptr<std::istream>& spStream) throw();
	void ClearActions() throw();
	void AddAction(uint32_t uActionID, const std::shared_ptr<RdScannerAction>& spAction);
	void Start(uint32_t uStartAction, RdToken& token) throw();
	bool GetToken(RdToken& token);

private:
	//map: <action id, action>
	std::map<uint32_t, std::shared_ptr<RdScannerAction>>  m_map;
	//stream
	std::shared_ptr<std::istream>  m_spStream;
	//stack
	RdActionStack  m_stack;
	//start action
	uint32_t m_uStartAction;
};

//LL actions
#define LA_NULL     (0)

//rule table
typedef struct _tagRuleElement
{
	uint32_t uToken;
	uint32_t uAction;
} RULEELEMENT;

typedef struct _tagRuleItem
{
	const RULEELEMENT* pRule;
	uintptr_t uNum;
} RULEITEM;

// push-down stack
typedef std::stack<RULEELEMENT>  RdPushDownStack;

// push-down table
class RdaTable
{
private:
	struct _TableItem
	{
		int32_t  iEpsilon;  // < 0 : -1 (start symbol) -2 ~ X (value+2 is the index of epsilon rule)
		//terminal id -> action
		std::map<uint32_t, int32_t>  mapTerminal;
		//follow
		std::set<uint32_t>  sFollow;
	};

public:
	RdaTable() throw();
	RdaTable(const RdaTable&) = delete;
	RdaTable& operator=(const RdaTable&) = delete;
	~RdaTable() throw();

	bool Generate(const RULEELEMENT* pRules, uint32_t uMaxTerminalID);

	//tools
	uint32_t GetStartNT() const throw();

	//return value: > 0 (push rule no) = 0 (error) < 0 (pop rule no)
	int32_t Input(uint32_t uNonterminal, uint32_t uTerminal) throw();

	void GetRule(uintptr_t index, RULEITEM& item) const throw();

private:
	static bool index_to_action(uintptr_t index, bool bPop, int32_t& iAct) throw();
	bool generate_first_set(uint32_t uMaxTerminalID);
	bool add_follow_set(uint32_t uMaxTerminalID);

private:
	//Nonterminal -> item
	std::map<uint32_t, std::shared_ptr<_TableItem>>  m_map;
	//rules
	std::vector<RULEITEM> m_rules;
	//start symbol
	uint32_t m_uStartNT;
};

// parser action
//   [](const std::string& strToken, std::vector<std::string>& vecError)->bool
typedef std::function<bool(const std::string&, std::vector<std::string>&)>  RdParserAction;

// RdParser
class RdParser
{
public:
	RdParser() throw();
	RdParser(const RdParser&) = delete;
	RdParser& operator=(const RdParser&) = delete;
	~RdParser() throw();

	void SetScanner(const std::shared_ptr<RdScanner>& sp) throw();
	void SetTable(const std::shared_ptr<RdaTable>& sp) throw();
	void ClearActions() throw();
	void AddAction(uint32_t uActionID, RdParserAction&& rpa);
	void SetAcceptedAction(RdParserAction&& rpa) throw();
	void Start(uint32_t uScannerStartAction, uint32_t uMaxTerminalID);
	//return value: < 0 (error, -1 means it can be reverted), = 0 (end), > 0 (succeeded)
	int32_t Parse(bool& bEmpty);
	bool Revert();

	//info
	bool IsEmpty() const throw();
	const std::vector<std::string>& GetErrorArray() const throw();

private:
	void append_unexpected_error();
	bool do_action(uint32_t uActionID);

private:
	//<action-id, action>
	std::map<uint32_t, RdParserAction>  m_map;
	RdParserAction  m_rpaAccepted;
	std::shared_ptr<RdScanner>  m_spScanner;
	std::shared_ptr<RdaTable>  m_spTable;
	uint32_t  m_uMaxTerminalID;

	std::vector<std::string>  m_vecError;
	RdPushDownStack  m_stack;
	RdToken  m_token;
	uint32_t  m_uCurrentEvent;
	bool  m_bEmpty;
};

// RdAllocator

class RdAllocator
{
public:
	RdAllocator() throw();
	RdAllocator(const RdAllocator&) = delete;
	RdAllocator& operator=(const RdAllocator&) = delete;
	~RdAllocator() throw();

	uint32_t Allocate(uint32_t uBytes);
	void* ToPointer(uint32_t uAddress) throw();
	const void* ToPointer(uint32_t uAddress) const throw();

private:
	std::vector<uint8_t>  m_vec;
};

// RdMetaDataPosition
struct RdMetaDataPosition
{
	uint32_t  uAddress;
};
// RdMetaDataInfo
struct RdMetaDataInfo
{
	const char*  szKey;
	uint32_t  uType;
	uint32_t  uLevel;
	RdMetaDataPosition  posData;
};
// RdMetaAstNodeInfo
struct RdMetaAstNodeInfo
{
	uint32_t uType;
	RdMetaDataPosition posParent;
	RdMetaDataPosition posChild;
	RdMetaDataPosition posNext;
	RdMetaDataPosition posData;
};

// RdMetaData

class RdMetaData
{
private:
	struct _SymbolNode
	{
		uint32_t uFlags;
		uint32_t uLevel;
		uint32_t uKey;
		uint32_t uHashCode;
		uint32_t uHashNext;
		uint32_t uLevelNext;
		uint32_t uData;
	};

	//constants
	enum { MAX_LEVEL = 0x7FFFFFFF, MASK_LEVEL = MAX_LEVEL, MASK_ANALYSIS = 0x80000000,
		RSHIFT_BITS = 31 };

	struct _AstNode
	{
		uint32_t uType;
		uint32_t uParent;
		uint32_t uChild;
		uint32_t uNext;
		uint32_t uData;
	};

public:
	RdMetaData() throw();
	RdMetaData(const RdMetaData&) = delete;
	RdMetaData& operator=(const RdMetaData&) = delete;
	~RdMetaData() throw();

	uint32_t CalcHash(const char* szSymbol);

	RdMetaDataPosition Find(const char* szSymbol, uint32_t uHashCode) const throw();
	RdMetaDataPosition FindNext(RdMetaDataPosition pos) const throw();
	RdMetaDataPosition GetZeroLevelHead() const throw();
	RdMetaDataPosition GetLevelNext(RdMetaDataPosition pos) const throw();
	void GetInfo(RdMetaDataPosition pos, RdMetaDataInfo& info, bool& bAnalysis) const throw();
	void SetType(RdMetaDataPosition pos, uint32_t uType) throw();
	void SetLevel(RdMetaDataPosition pos, uint32_t uLevel) throw();
	void SetData(RdMetaDataPosition pos, RdMetaDataPosition posData) throw();
	void ClearAnalysisFlag(RdMetaDataPosition pos) throw();
	RdMetaDataPosition InsertSymbol(const char* szSymbol, uint32_t uType, bool bLevelLink);

	void EnterLevel();
	RdMetaDataPosition LeaveLevel(bool bReverseLevelLink) throw();
	uint32_t GetCurrentLevel() const throw();
	void FinishZeroLevel(bool bReverseLevelLink) throw();
	RdMetaDataPosition ReverseLevelLink(RdMetaDataPosition pos) throw();

	RdMetaDataPosition InsertData(uint32_t uSize);
	void* GetData(RdMetaDataPosition pos) throw();
	const void* GetData(RdMetaDataPosition posData) const throw();

	RdMetaDataPosition InsertAstNode(uint32_t uType);
	void SetAstParent(RdMetaDataPosition pos, RdMetaDataPosition posParent) throw();
	void SetAstChild(RdMetaDataPosition pos, RdMetaDataPosition posChild) throw();
	void SetAstNext(RdMetaDataPosition pos, RdMetaDataPosition posNext) throw();
	void SetAstData(RdMetaDataPosition pos, RdMetaDataPosition posData) throw();
	void GetAstNodeInfo(RdMetaDataPosition pos, RdMetaAstNodeInfo& info) const throw();
	void SetAstLinkParent(RdMetaDataPosition posHead, RdMetaDataPosition posParent) throw();
	RdMetaDataPosition ReverseAstLink(RdMetaDataPosition posHead) throw();
	RdMetaDataPosition GetAstStart() const throw();
	void ResetAst() throw();
	RdMetaDataPosition GetAstRoot(RdMetaDataPosition posStart) const throw();

private:
	RdMetaDataPosition find_next(const char* szSymbol, uint32_t uHashCode, RdMetaDataPosition pos) const throw();
	uint32_t reverse_level_link(uint32_t uHead) throw();

private:
	RdAllocator m_raString;
	RdAllocator m_raPool;
	RdAllocator m_raData;
	RdAllocator m_raAst;

	//hash map
	uint32_t m_uSymbolStart;
	uint32_t m_uBins;
	uint32_t m_uZeroLevelHead;
	//ast
	uint32_t m_uAstStart;

	//stack
	std::stack<uint32_t> m_stkLevel;
};

//Meta data for parser actions
struct RdParserActionMetaData
{
	std::shared_ptr<RdMetaData> spMeta;
	RdMetaDataPosition posParent;
	RdMetaDataPosition posCurrent;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
