/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../view/TextEditor.h"
#include "MainWindow.h"
#include "ReplaceDialog.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// MainWindow

MainWindow::MainWindow(int w, int h, const char* t) : Fl_Double_Window(w, h, t), 
                                                      m_textEditor(std::make_shared<TextEditor>(50, 80, 400, 400)), 
	                                                  m_menuBar(std::make_shared<Fl_Menu_Bar>(0, 0, 500, 40)),
													  m_replaceDlg(std::make_shared<ReplaceDialog>(300, 105, "Replace"))
{
	m_menuBar->add("Load...", 0, &load_cb, &m_cmdFunc_load);
	m_menuBar->add("Save...", 0, &save_cb, &m_cmdFunc_save);
	m_menuBar->add("Replace...", 0, &replace_cb, m_replaceDlg.get());
	
	this->resizable(*m_textEditor);
}

MainWindow::~MainWindow() noexcept
{
}

//properties
std::shared_ptr<TextEditor> MainWindow::get_TextEditor() noexcept
{
	return m_textEditor;
}

//commands
void MainWindow::set_LoadCommand(CommandFunc&& cf)
{
	m_cmdFunc_load = std::move(cf);
}

void MainWindow::set_SaveCommand(CommandFunc&& cf)
{
	m_cmdFunc_save = std::move(cf);
}

//callbacks
void MainWindow::load_cb(Fl_Widget*, void* v)
{
	Fl_Native_File_Chooser fc;
	fc.title("Choose file");
	fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	if (fc.show() == 0) {
		CommandFunc& cmdFunc = *((CommandFunc*)v);
		if (cmdFunc != nullptr && !cmdFunc(std::make_any<std::string>(std::string(fc.filename())))){
			fl_alert("Error in opening file!");
		}
	}
	return;
}

void MainWindow::save_cb(Fl_Widget*, void* v)
{
	Fl_Native_File_Chooser fc;
	fc.title("Save file");
	fc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	if (fc.show() == 0) {
		CommandFunc& cmdFunc = *((CommandFunc*)v);
		if (cmdFunc != nullptr && !cmdFunc(std::make_any<std::string>(std::string(fc.filename())))) {
			fl_alert("Error in saving file!");
		}
	}
	return;
}

void MainWindow::replace_cb(Fl_Widget*, void* v)
{
	ReplaceDialog* dialog = (ReplaceDialog*)v;
	dialog->show();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
