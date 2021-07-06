/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

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
	m_menuBar.add("Config...", 0, &config_cb, &m_cmdConfig);

	callback((Fl_Callback*)&close_cb, &m_cmdClose);

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

//properties
void MainWindow::attach_BackColor(const RefPtr<Fl_Color>& refColor) noexcept
{
	m_refBackColor = refColor;
}
RefPtr<Fl_Color> MainWindow::detach_BackColor() noexcept
{
	return RefPtr<Fl_Color>(std::move(m_refBackColor));
}

//commands
void MainWindow::attach_LoadCommand(std::function<bool(const std::string&)>&& cf) noexcept
{
	m_cmdLoad = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_LoadCommand() noexcept
{
	return std::function<bool(const std::string&)>(std::move(m_cmdLoad));
}
void MainWindow::attach_SaveCommand(std::function<bool(const std::string&)>&& cf) noexcept
{
	m_cmdSave = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_SaveCommand() noexcept
{
	return std::function<bool(const std::string&)>(std::move(m_cmdSave));
}
void MainWindow::attach_ReplaceCommand(std::function<bool()>&& cf) noexcept
{
	m_cmdReplace = std::move(cf);
}
std::function<bool()> MainWindow::detach_ReplaceCommand() noexcept
{
	return std::function<bool()>(std::move(m_cmdReplace));
}
void MainWindow::attach_ConfigCommand(std::function<void()>&& cf) noexcept
{
	m_cmdConfig = std::move(cf);
}
std::function<void()> MainWindow::detach_ConfigCommand() noexcept
{
	return std::function<void()>(std::move(m_cmdConfig));
}
void MainWindow::attach_CloseCommand(std::function<void()>&& cf) noexcept
{
	m_cmdClose = std::move(cf);
}
std::function<void()> MainWindow::detach_CloseCommand() noexcept
{
	return std::function<void()>(std::move(m_cmdClose));
}

//methods
void MainWindow::Update()
{
	this->color(*m_refBackColor);
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

void MainWindow::config_cb(Fl_Widget*, void* v)
{
	std::function<bool()>& cmdFunc = *((std::function<bool()>*)v);
	if ( cmdFunc != nullptr ) {
		cmdFunc();
	}
}

void MainWindow::close_cb(Fl_Window* pW, void* pD)
{
	std::function<void()>& cf = *((std::function<void()>*)pD);
	if( cf != nullptr )
		cf();
	default_callback(pW, pD);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
