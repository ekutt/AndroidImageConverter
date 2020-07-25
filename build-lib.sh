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
