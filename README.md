Image Converter Application for Android
==============================================
Android JPEG to TIFF converter native application project.

The aim of this project is to provide an example Android application code that uses native C/C++ libraries.

## Building 
### Requirements
- Android NDK r21d
- Android SDK
- Android SDK Build tools 30.0.0
- libjpeg v9d
- libtiff v4.1.0
- CMake 3.10.2

Edit 'buildToolsVersion' in 'build.gradle' files if necessary.

Clone this project and create local.properties file under project root directory.
Add the following properties to local.properties file with directory information 
where you installed Android sdk and ndk:

	sdk.dir=<SDK_INSTALL_DIR>
	ndk.dir=<NDK_INSTALL_DIR>

#### Building The Project
The project is in Gradle project format. There are numerous ways you can build the project: 
- Open the project in Android Studio and build.
- Alternatively, you can open the terminal under project root directory and run the following command:
	./gradlew build 







