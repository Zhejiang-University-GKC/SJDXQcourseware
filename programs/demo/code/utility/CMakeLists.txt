INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/others/wtl/include"
	"${PROJECT_SOURCE_DIR}/others/etl/include"
	"${PROJECT_SOURCE_DIR}/utility"
	)
SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_LIST "common/BusInfo.cpp" "common/parameters.cpp"
	"model/BusDataModel.cpp"
	"viewmodel/BusViewModel.cpp"
	"viewmodel/sinks/BusViewModelSink.cpp"
	"viewmodel/commands/QueryCommand.cpp"
	)
ADD_LIBRARY(utility STATIC ${SRC_LIST})
SET_TARGET_PROPERTIES(utility PROPERTIES OUTPUT_NAME "utility"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET_W}")
