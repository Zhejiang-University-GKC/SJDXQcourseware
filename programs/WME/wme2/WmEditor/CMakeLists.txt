#
# Xin YUAN, 2019, BSD (2)
#

# target

INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/WmarkEditor/src"
	)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_PCH_LIST "precomp.cpp")
SET(SRC_LIST "src/main.cpp"
	"src/model/TextModel.cpp"
	"src/model/CfgModel.cpp"
	"src/viewmodel/notifications/TextViewModelNotification.cpp"
	"src/viewmodel/notifications/CfgViewModelNotification.cpp"
	"src/viewmodel/commands/LoadCommand.cpp"
	"src/viewmodel/commands/SaveCommand.cpp"
	"src/viewmodel/commands/SetBackColorCommand.cpp"
	"src/viewmodel/TextViewModel.cpp"
	"src/viewmodel/CfgViewModel.cpp"
	"src/view/TextEditor.cpp"
	"src/window/notifications/MainWindowNotification.cpp"
	"src/window/notifications/ReplaceDialogNotification.cpp"
	"src/window/MainWindow.cpp"
	"src/window/ReplaceDialog.cpp"
	"src/window/CfgDialog.cpp"
	"src/app/commands/ReplaceCommand.cpp"
	"src/app/commands/CloseReplaceCommand.cpp"
	"src/app/commands/ConfigCommand.cpp"
	"src/app/ReplacePart.cpp"
	"src/app/TextPart.cpp"
	"src/app/CfgPart.cpp"
	"src/app/TextApp.cpp"
	)
ADD_EXECUTABLE(WmarkEditor ${SRC_PCH_LIST} ${SRC_LIST})
SET_PCH(WmarkEditor "exe" "precomp.h" ${SRC_PCH_LIST} ${SRC_LIST})
SET_TARGET_PROPERTIES(WmarkEditor PROPERTIES
	OUTPUT_NAME "WmarkEditor"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET}")
TARGET_LINK_LIBRARIES(WmarkEditor ${STRING_CSL_LIBS} ${STRING_FLTK_LIBS} ${STRING_LINK_EXTRA_LIBS})

#end
