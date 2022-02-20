////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "app/PcApp.h"

////////////////////////////////////////////////////////////////////////////////

CAppModule _Module;

////////////////////////////////////////////////////////////////////////////////

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);

	HRESULT hRes = _Module.Init(NULL, hInstance);
	hRes;
	ATLASSERT(SUCCEEDED(hRes));
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	//----------------------------------------------------------------------
	PcApp app;
	if( !app.Init() ) {
		ATLTRACE(_T("Main window creation failed!\n"));
		_Module.RemoveMessageLoop();
		_Module.Term();
		return 1;
	}
	app.Show(nCmdShow);
	//----------------------------------------------------------------------

	int nRet = theLoop.Run();
	_Module.RemoveMessageLoop();
	_Module.Term();

	return nRet;
}

////////////////////////////////////////////////////////////////////////////////
