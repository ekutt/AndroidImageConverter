JPEG to TIFF Image Converter Application for Android
==============================================
Android JPEG to TIFF converter native application project.

The aim of this project is to show an application which uses native C/C++ libraries.

Building The Project
---------------------------------
Requirements
- Android NDK r21d
- Android SDK
- Android SDK Build tools 30.0.0
- CMake 3.10.2

Edit 'buildToolsVersion' in 'build.gradle' files if necessary.

Clone this project and create local.properties file under project root directory.
Add the following properties to local.properties file with directory information 
where you installed Android sdk and ndk:
Add the following information in local.properties file:

	sdk.dir=<SDK_INSTALL_DIR>
	ndk.dir=<NDK_INSTALL_DIR>

#### Building & Deploying The Dependencies
You must build libjpeg and libtiff dependencies before you can build the project. 

Extract libtiff v4.1.0 source, copy the build-lib.sh file from project root directory to libtiff source root directory.
Open terminal in libtiff source root directory and execute the script. Library will be installed to "install"
directory under libtiff source root directory. Follow the same steps for libjpeg also.

Copy the libtiff.so, libjpeg.so from install directories and libz.so from ndk to corresponding directories(x86, x86_64, armeabi-v7a, arm64-v8a)
in project depending on target device architecture. 

#### Building The Project

The project is in Gradle project format. There are numerous ways you can build the project: 
- Open the project in Android Studio and build.
- Alternatively, you can open the terminal under project root directory and run the following command:

	./gradlew build 

