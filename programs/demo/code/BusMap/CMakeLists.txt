INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/others/wtl/include"
	"${PROJECT_SOURCE_DIR}/others/etl/include"
	"${PROJECT_SOURCE_DIR}/utility"
	"${PROJECT_SOURCE_DIR}/BusMap"
	)
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_LIST "main.cpp"
	"view/BusLabel.cpp"
	"window/MainWindow.cpp"
	"window/sinks/MainWindowPropertySink.cpp"
	"window/sinks/MainWindowCommandSink.cpp"
	"app/BusApp.cpp"
	)
ADD_EXECUTABLE(BusMap ${SRC_LIST})
SET_TARGET_PROPERTIES(BusMap PROPERTIES OUTPUT_NAME "BusMap"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET_W}")
TARGET_LINK_LIBRARIES(BusMap utility)

#pack
INSTALL(TARGETS BusMap
	RUNTIME DESTINATION bin COMPONENT runtime
)


INSTALL(DIRECTORY "${PROJECT_SOURCE_DIR}/others/redist/x64/Release/"

	DESTINATION bin COMPONENT runtime

	CONFIGURATIONS Release)
