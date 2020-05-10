﻿/*
** XIN YUAN, 2020, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __TEXT_PART_H__
#define __TEXT_PART_H__
////////////////////////////////////////////////////////////////////////////////

#include "../model/TextModel.h"
#include "../viewmodel/TextViewModel.h"
#include "../view/TextEditor.h"
#include "../window/MainWindow.h"

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// TextPart

class TextPart
{
public:
	TextPart();
	TextPart(const TextPart&) = delete;
	TextPart& operator=(const TextPart&) = delete;
	~TextPart() noexcept;

public:
	MainWindow& GetMainWindow() noexcept;

private:
	TextModel      m_model;
	TextViewModel  m_textVM;
	MainWindow     m_wndMain;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
