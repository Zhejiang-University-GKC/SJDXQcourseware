INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/utility"
	"${PROJECT_SOURCE_DIR}/BusMap"
	)
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_PCH_LIST "precomp.cpp")
SET(SRC_LIST "main.cpp"
	"view/BusLabel.cpp"
	"window/MainWindow.cpp"
	"window/sinks/MainWindowPropertySink.cpp"
	"window/sinks/MainWindowCommandSink.cpp"
	"window/states/StartState.cpp"
	"window/states/PopupState.cpp"
	"window/states/CaptureState.cpp"
	"app/BusApp.cpp"
	)
SET(RC_LIST "rc/BusMap.rc")
ADD_EXECUTABLE(BusMap ${SRC_PCH_LIST} ${SRC_LIST} ${RC_LIST})
SET_PCH("exe" "precomp.h" ${SRC_PCH_LIST} ${SRC_LIST})
SET_TARGET_PROPERTIES(BusMap PROPERTIES OUTPUT_NAME "BusMap"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET_W}")
TARGET_LINK_LIBRARIES(BusMap utility)

#pack
INSTALL(TARGETS BusMap
	RUNTIME DESTINATION bin COMPONENT runtime
)

INSTALL(DIRECTORY "${PROJECT_SOURCE_DIR}/others/ETL/third/redist/x64/Release/"
	DESTINATION bin COMPONENT runtime
	CONFIGURATIONS Release)
