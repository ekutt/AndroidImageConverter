Image Converter Application for Android
==============================================

|Linux|
|:----------------:|
| ![.github/workflows/build.yml](https://github.com/ekutt/AndroidImageConverter/workflows/.github/workflows/build.yml/badge.svg?branch=master) | 

Android JPEG to TIFF converter native application project.
The aim of this project is to provide an example Android application code that uses native C/C++ libraries.

## Building 
### Requirements
- Android NDK r21d
- Android SDK
- Android SDK Build tools 30.0.0
- CMake 3.10.2

Edit 'buildToolsVersion' in 'build.gradle' files if necessary.

Clone this project and create local.properties file under project root directory.
Add the following properties to local.properties file with directory information where you installed Android sdk and ndk:

	sdk.dir=<SDK_INSTALL_DIR>
	ndk.dir=<NDK_INSTALL_DIR>

#### Building The Project

The project is in Gradle project format. There are numerous ways you can build the project: 
- Open the project in Android Studio and run build.
- Alternatively, you can open the terminal under project root directory and run the following 
command:

	./gradlew build 
	
- Image converter application uses libjpeg-9d and libtiff-4.1.0 C libraries. The dependencies are already cross built and integrated into project, you don't have to build them. The dependency headers are kept in 3rd-party folder under project root directory and shared object libraries are kept in app/src/libs directory under corresponding target architecture folder:

![alt text](https://github.com/ekutt/AndroidImageConverter/blob/assets/assets/dependencies.png)

If you wonder how to build and deploy them in case you wanted to create a project from scratch, you can continue reading.
	

#### Building The Dependencies
**Note:** Autoconf projects are generally not buildable on Windows. Windows users can build the libraries using WSL or MSYS.

##### Cross Building LibTIFF with Clang for Android
Extract the libtiff source to the directory of your choice and copy and run the following script (build-lib.sh) to the libtiff source root 
directory.

	#!/bin/bash
	export NDK=<NDK-INSTALL-DIR>
	# Only choose one of these, depending on your development platform
	# export HOST_TAG=linux-x86_64
	# export HOST_TAG=darwin-x86_64
	# export HOST_TAG=windows
	# export HOST_TAG=windows-x86_64
	export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG

	# Only choose one of these, depending on your target device
	#export TARGET=aarch64-linux-android
	#export TARGET=arm-linux-androideabi
	#export TARGET=i686-linux-android
	#export TARGET=x86_64-linux-android

	# Set this to your minSdkVersion.
	export API=21

	# Configure and build.
	export AR=$TOOLCHAIN/bin/$TARGET-ar
	export AS=$TOOLCHAIN/bin/$TARGET-as

	if [ "$TARGET" == "arm-linux-androideabi" ]; then
	export CC=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang
	export CXX=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang++
	else
	export CC=$TOOLCHAIN/bin/$TARGET$API-clang
	export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++
	fi

	#We are not setting CPP C preprocessor environment variable, "$CC -E" invokes the clang C preprocessor
	export LD=$TOOLCHAIN/bin/$TARGET-ld
	export RANLIB=$TOOLCHAIN/bin/$TARGET-ranlib
	export STRIP=$TOOLCHAIN/bin/$TARGET-strip

	./configure --host=$TARGET --prefix=`pwd`/install 
	make 
	make install

build-lib.sh script does the necessary job of setting up environment variables so that the build scripts call the correct cross compilation tools in NDK. What you have to do in the build-lib.sh script is to change <NDK-INSTALL-DIR> to the directory where you have installed Android NDK to (e.g. /home/testUser/android-ndk-r21d). Uncomment the corresponding TARGET line depending on your target platform and execute the script at the root directory of libtiff source. Libtiff has zlib dependency but there is no need to cross build zlib since prebuilt zlib library is already shipped with ndk-r21d.
Running build-lib.sh script should successfully build the libtiff and install the headers and compiled binaries to “install” folder under libtiff source root directory.
	
##### Cross Building LibJPEG with Clang for Android
Extract the libjpeg source to the directory of your choice and copy the same build-lib.sh script we used in previous section to the libjpeg source root directory. Follow the script modification steps as mentioned in previous section and execute the script from the root directory of libjpeg source. Running build-lib.sh script should successfully build the libjpeg and install the headers and compiled binaries to “install” folder under libjpeg source root directory.

##### Deploying The Libraries in Android Studio Project
We need to deploy libjpeg and libtiff shared libraries into Android Studio Project. We want Gradle to package our prebuilt native libraries that are not used in any external native build. Since we are using Gradle plugin 4.0, we need to keep prebuilt libraries in a directory other than jniLibs. (Important: Please don’t forget to copy libz.so from ndk package. Libtiff has libz dependency.) So, we add them to the src/main/libs/ABI directory of our module. Deployment should look like follows:

![alt text](https://github.com/ekutt/AndroidImageConverter/blob/assets/assets/dependencies.png)

