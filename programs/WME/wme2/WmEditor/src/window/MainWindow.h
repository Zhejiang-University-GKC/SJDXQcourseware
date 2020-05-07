/*
** Anxiu Li, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// MainWindow

class MainWindow : public Fl_Double_Window
{
public:
	MainWindow(int w, int h, const char* t);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	~MainWindow() noexcept;

//widgets
	TextEditor& GetTextEditor() noexcept;

//commands
	void attach_LoadCommand(std::function<bool(const std::string&)>&& cf) noexcept;
	std::function<bool(const std::string&)> detach_LoadCommand() noexcept;
	void attach_SaveCommand(std::function<bool(const std::string&)>&& cf) noexcept;
	std::function<bool(const std::string&)> detach_SaveCommand() noexcept;
	void attach_ReplaceCommand(std::function<bool()>&& cf) noexcept;
	std::function<bool()> detach_ReplaceCommand() noexcept;

//notifications
	PropertyNotification get_Notification();

private:
//callbacks
	static void load_cb(Fl_Widget*, void* v);
	static void save_cb(Fl_Widget*, void* v);
	static void replace_cb(Fl_Widget*, void* v);

private:
//commands
	std::function<bool(const std::string&)> m_cmdLoad;
	std::function<bool(const std::string&)> m_cmdSave;
	std::function<bool()> m_cmdReplace;

//UI
	TextEditor   m_textEditor;
	Fl_Menu_Bar  m_menuBar;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

