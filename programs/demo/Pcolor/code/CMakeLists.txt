INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/code"
	)
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_PCH_LIST "precomp.cpp")
SET(SRC_LIST "main.cpp"
	"common/PcCfg.cpp"
	"model/CfgModel.cpp"
	"model/ColorModel.cpp"
	"viewmodel/commands/LoadGrayImageCommand.cpp"
	"viewmodel/commands/SaveColorImageCommand.cpp"
	"viewmodel/commands/LoadCfgCommand.cpp"
	"viewmodel/commands/SaveCfgCommand.cpp"
	"viewmodel/commands/ModifyColorPointCommand.cpp"
	"viewmodel/sinks/ColorViewModelSink.cpp"
	"viewmodel/ColorViewModel.cpp"
	"window/sinks/MainWindowPropertySink.cpp"
	"window/sinks/MainWindowCommandSink.cpp"
	"window/MainWindow.cpp"
	"app/PcApp.cpp"
	)
ADD_EXECUTABLE(PcTool ${SRC_PCH_LIST} ${SRC_LIST})
SET_PCH("exe" "precomp.h" ${SRC_PCH_LIST} ${SRC_LIST})
SET_TARGET_PROPERTIES(PcTool PROPERTIES OUTPUT_NAME "PcTool"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET_W}")

#pack
INSTALL(TARGETS PcTool
	RUNTIME DESTINATION bin COMPONENT runtime
)

INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../cfg/sample.txt"
	DESTINATION cfg COMPONENT runtime)
INSTALL(DIRECTORY "${PROJECT_SOURCE_DIR}/../others/ETL/third/redist/x64/Release/"
	DESTINATION bin COMPONENT runtime
	CONFIGURATIONS Release)
