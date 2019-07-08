
# Compiling

1. Debug

	```
	cd <work-directory>
	<cmake-directory>\cmake <source-directory>\demo\code -G "Visual Studio 16" -A x64
	MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Debug
	cd test
	<cmake-directory>\ctest -C "Debug"
	```

1. Release

	```
	cd <work-directory>
	<cmake-directory>\cmake <source-directory>\demo\code -G "Visual Studio 16" -A x64
	MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Release
	<cmake-directory>\cpack -D CPACK_GENERATOR="ZIP"
	```
