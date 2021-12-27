
# WmEditor

## Compiling

1. Windows

	```
	<cmake directory>\bin\cmake <WME directory> -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -A x64
	MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Debug
	```

	```
	<cmake directory>\bin\cmake <WME directory> -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A x64
	MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Release
	```

1. Linux

	```
	<cmake directory>\bin\cmake <WME directory> -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
	make
	```

	```
	<cmake directory>\bin\cmake <WME directory> -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
	make
	```
