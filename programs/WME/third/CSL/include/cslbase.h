/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __CSL_BASE_H__
#define __CSL_BASE_H__
////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <cassert>
#include <cstring>

#include <memory>
#include <vector>
#include <stack>
#include <map>
#include <set>

#include <string>
#include <codecvt>
#include <cwchar>
#include <locale>

#include <stdexcept>
#include <fstream>
#include <iostream>

#include <functional>
#include <tuple>
#include <limits>

#include <thread>
#include <chrono>

//C++17
#ifdef CPP_17
#include <filesystem>
#include <any>
#endif

////////////////////////////////////////////////////////////////////////////////

// types

// entry point

#ifdef WIN32
#define CSL_UI_MAIN_ENTRY()  \
	int APIENTRY WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
#else
#define CSL_UI_MAIN_ENTRY()  \
	int main(int argc, char* argv[])
#endif

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

//pointer

template <typename T>
class RefPtr
{
public:
	RefPtr() noexcept : m_p(nullptr)
	{
	}
	explicit RefPtr(T& t) noexcept : m_p(&t)
	{
	}
	explicit RefPtr(T* p) noexcept : m_p(p)
	{
	}
	RefPtr(const RefPtr& src) noexcept : m_p(src.m_p)
	{
	}
	RefPtr(RefPtr&& src) noexcept : m_p(src.m_p)
	{
		src.m_p = nullptr;
	}
	~RefPtr() noexcept
	{
	}

	RefPtr& operator=(const RefPtr& src) noexcept
	{
		m_p = src.m_p;
		return *this;
	}
	RefPtr& operator=(RefPtr&& src) noexcept
	{
		m_p = src.m_p;
		src.m_p = nullptr;
		return *this;
	}

	void Reset() noexcept
	{
		m_p = nullptr;
	}

	bool IsNull() const noexcept
	{
		return m_p == nullptr;
	}

	const T* Get() const noexcept
	{
		return m_p;
	}
	T* Get() noexcept
	{
		return m_p;
	}
	const T* operator->() const noexcept
	{
		return Get();
	}
	T* operator->() noexcept
	{
		return Get();
	}
	const T& operator*() const noexcept
	{
		assert( !IsNull() );
		return *Get();
	}
	T& operator*() noexcept
	{
		assert( !IsNull() );
		return *Get();
	}

private:
	T* m_p;
};

//operators

class SafeOperators
{
public:
	//T : unsigned integer types
	template <typename T>
	static T AddThrow(T left, T right)
	{
		T r = left + right;
		if( r < left )
			throw std::overflow_error("");
		return r;
	}
	template <typename T>
	static T MultiplyThrow(T left, T right)
	{
		//avoid divide 0
		if( left == 0 )
			return 0;
		if( std::numeric_limits<T>::max() / left < right )
			throw std::overflow_error("");
		return left * right;
	}
};

//code convert

class CodeConvertHelper
{
public:
	// Ansi -> wstring
	static void AnsiToWide(const char* sz1, std::wstring& str2);
	// wstring -> Ansi
	static void WideToAnsi(const wchar_t* sz1, std::string& str2);
	// UTF8 -> wstring
	static void UTF8ToWide(const char* sz1, std::wstring& str2);
	static void UTF8ToWide(const std::string& str1, std::wstring& str2);
	// wstring -> UTF8
	static void WideToUTF8(const wchar_t* wsz1, std::string& str2);
	static void WideToUTF8(const std::wstring& str1, std::string& str2);
};

//path

class FsPathHelper
{
public:
	static void ToPlatform(char* szBuffer) throw();
	static const char* GetHomeDirectory() throw();
};

//stream

class StreamHelper
{
public:
	//return: true -- has UTF8 BOM
	static bool CheckBOM_UTF8(std::istream& stm);
};

//test

class TestBody
{
public:
	//T : Lambda
	template <typename T>
	static bool Run(const T& t) throw()
	{
		try {
			t();
		}
		catch(...) {
			//**********
			std::cout << "Exception error: (" << __FILE__ << ")(" << __LINE__ << ")" << std::endl;
			//**********
			return false;
		}
		return true;
	}
	static void Assert(bool bValue, const char* szFile, int iLineNum)
	{
		if( !bValue ) {
			//**********
			std::cout << "Assert error: (" << szFile << ")(" << iLineNum << ")" << std::endl;
			//**********
			throw std::exception();
		}
	}
	//T : Lambda
	template <typename T>
	static void Exception(const T& t)
	{
		try {
			t();
		}
		catch(...) {
			//**********
			std::cout << "Correct Exception : (" << __FILE__ << ")(" << __LINE__ << ")" << std::endl;
			//**********
			return ;
		}
		Assert(false, __FILE__, __LINE__);
	}
};

//framework

// Command
//   [](<parameters>)->bool
//   provider class: std::function<bool(...)> get_XXXCommand();
//   binding class: void attach_XXXCommand(std::function<bool(...)>&& cmd);
//                  std::function<bool(...)> detach_XXXCommand() noexcept;

#ifdef CPP_17
//   [](std::any&& param)->bool
typedef std::function<bool(std::any&&)>  CommandFunc;
#endif

// Property Notification
//   [](uint32_t)
typedef std::function<void(uint32_t)>  PropertyNotification;

class PropertyTrigger
{
public:
	PropertyTrigger() noexcept;
	PropertyTrigger(const PropertyTrigger&) = delete;
	PropertyTrigger& operator=(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept;

	void ClearNotifications() noexcept;
	uintptr_t AddNotification(PropertyNotification&& pn);
	void RemoveNotification(uintptr_t uCookie) noexcept;

	void Fire(uint32_t uID);

private:
	std::vector<PropertyNotification> m_vecPN;
};

// state machine

typedef std::function<int32_t(uint32_t)>  StateFunc;
//   provider class: StateFunc get_XXXStateFunc();

class StateManager
{
public:
	StateManager() noexcept;
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;
	~StateManager() noexcept;

	void Add(int32_t iState, StateFunc&& sf)
	{
		m_map.insert(std::pair<int32_t, StateFunc>(iState, std::move(sf)));
	}
	void SetStartState(int32_t iStartState) noexcept
	{
		m_iCurrentState = iStartState;
	}
	void Process(uint32_t uEvent)
	{
		auto iter(m_map.find(m_iCurrentState));
		if( iter != m_map.end() )
			m_iCurrentState = iter->second(uEvent);
	}
	int32_t GetCurrentState() const noexcept
	{
		return m_iCurrentState;
	}

private:
	int32_t m_iCurrentState;
	std::map<int32_t, StateFunc> m_map;
};

/*
class ParameterBase
{
public:
	uint32_t m_uType;
};

class IStateBase
{
public:
	//virtual int32_t Process(uint32_t uEvent, const std::shared_ptr<ParameterBase>& param) = 0;
	virtual int32_t Process(uint32_t uEvent, const std::any& param) = 0;
};

class StateManager
{
public:
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;

	void Add(int32_t iState, const std::shared_ptr<IStateBase>& spState)
	{
		m_map.insert(std::pair<int32_t, std::shared_ptr<IStateBase>>(iState, spState));
	}
	void SetStartState(int32_t iStartState) throw()
	{
		m_iCurrentState = iStartState;
	}
	void Process(uint32_t uEvent, const std::any& param)
	{
		auto iter(m_map.find(m_iCurrentState));
		if( iter != m_map.end() )
			m_iCurrentState = iter->second->Process(uEvent, param);
	}
	int32_t GetCurrentState() const throw()
	{
		return m_iCurrentState;
	}

private:
	int32_t m_iCurrentState;
	std::map<int32_t, std::shared_ptr<IStateBase>> m_map;
};
*/

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
