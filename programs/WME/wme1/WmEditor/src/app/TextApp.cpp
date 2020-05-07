/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../model/TextModel.h"
#include "../viewmodel/TextViewModel.h"
#include "../view/TextEditor.h"
#include "../window/MainWindow.h"
#include "TextApp.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextApp

TextApp::TextApp()
{
}

TextApp::~TextApp() noexcept
{
}

//methods
bool TextApp::Init()
{
	m_wndMain = std::make_shared<MainWindow>(500, 500, "WmarkEditor");

	//objects
	std::shared_ptr<TextModel> spModel(std::make_shared<TextModel>());
	m_textVM = std::make_shared<TextViewModel>();
	m_textVM->SetModel(spModel);

	//binding

	//properties
	m_wndMain->get_TextEditor()->set_TextBuffer(m_textVM->get_TextBuf());

	//commands
	m_wndMain->set_LoadCommand(m_textVM->get_LoadCommand());
	m_wndMain->set_SaveCommand(m_textVM->get_SaveCommand());

	//notifications
	m_textVM->AddNotification(m_wndMain->get_Notification());

	return true;
}

int TextApp::Run()
{
	m_wndMain->show();
	return Fl::run();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
