/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../view/TextEditor.h"
#include "MainWindow.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// MainWindow

MainWindow::MainWindow(int w, int h, const char* t) : Fl_Double_Window(w, h, t), 
                                                      m_textEditor(50, 80, 400, 400), 
	                                                  m_menuBar(0, 0, 500, 40)
{
	end();
	m_menuBar.add("Load...", 0, &load_cb, &m_cmdLoad);
	m_menuBar.add("Save...", 0, &save_cb, &m_cmdSave);
	m_menuBar.add("Replace...", 0, &replace_cb, &m_cmdReplace);

	this->resizable(m_textEditor);
}

MainWindow::~MainWindow() noexcept
{
}

//widgets
TextEditor& MainWindow::GetTextEditor() noexcept
{
	return m_textEditor;
}

//commands
void MainWindow::attach_LoadCommand(std::function<bool(const std::string&)>&& cf) noexcept
{
	m_cmdLoad = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_LoadCommand() noexcept
{
	std::function<bool(const std::string&)> ret = std::move(m_cmdLoad);
	return ret;
}
void MainWindow::attach_SaveCommand(std::function<bool(const std::string&)>&& cf) noexcept
{
	m_cmdSave = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_SaveCommand() noexcept
{
	std::function<bool(const std::string&)> ret = std::move(m_cmdSave);
	return ret;
}
void MainWindow::attach_ReplaceCommand(std::function<bool()>&& cf) noexcept
{
	m_cmdReplace = std::move(cf);
}
std::function<bool()> MainWindow::detach_ReplaceCommand() noexcept
{
	std::function<bool()> ret = std::move(m_cmdReplace);
	return ret;
}

//callbacks
void MainWindow::load_cb(Fl_Widget*, void* v)
{
	Fl_Native_File_Chooser fc;
	fc.title("Choose file");
	fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	if (fc.show() == 0) {
		std::function<bool(const std::string&)>& cmdFunc = *((std::function<bool(const std::string&)>*)v);
		if ( cmdFunc != nullptr && !cmdFunc((std::string(fc.filename()))) ) {
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
		std::function<bool(const std::string&)>& cmdFunc = *((std::function<bool(const std::string&)>*)v);
		if ( cmdFunc != nullptr && !cmdFunc(std::string(fc.filename())) ) {
			fl_alert("Error in saving file!");
		}
	}
	return;
}

void MainWindow::replace_cb(Fl_Widget*, void* v)
{
	std::function<bool()>& cmdFunc = *((std::function<bool()>*)v);
	if ( cmdFunc != nullptr && !cmdFunc() ) {
		fl_alert("Error: Do not show replace dialog!");
	}
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
