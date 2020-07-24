#include "Image_jni.h"
#include "image/image.h"

#include <jni.h>
#include <iostream>

void rethrow_as_java_exception(JNIEnv* env)
{
    try
    {
        throw;
    }
    catch (const std::bad_alloc& e)
    {
        jclass jc = env->FindClass("java/lang/OutOfMemoryError");
        if(jc) env->ThrowNew (jc, e.what());
    }
    catch (const std::ios_base::failure& e)
    {
        jclass jc = env->FindClass("java/io/IOException");
        if(jc) env->ThrowNew (jc, e.what());
    }
    catch (const std::exception& e)
    {
        /* unknown exception (may derive from std::exception) */
        jclass jc = env->FindClass("java/lang/Exception");
        if(jc) env->ThrowNew (jc, e.what());
    }
    catch (...)
    {
        /* Oops I missed identifying this exception! */
        jclass jc = env->FindClass("java/lang/Error");
        if(jc) env->ThrowNew (jc, "Unidentified exception => "
                                  "Improve rethrow_cpp_exception_as_java_exception()" );
    }
}
/*
 * Class:     com_ekutt_example_imageconverter_ImageConverter
 * Method:    convertJPEGtoPNG_Native
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_ekutt_example_imageconverter_ImageConverter_convertJPEGtoPNG_1Native
        (JNIEnv* env, jclass, jstring filename, jstring saveFoldername)
{
  try
  {
    jboolean isCopy;
    const char *convertedStr = (env)->GetStringUTFChars(filename, &isCopy);
    const jsize length = (*env).GetStringLength(filename);

    const char *convertedFolderStr = (env)->GetStringUTFChars(saveFoldername, &isCopy);
    const jsize lengthFolder = (*env).GetStringLength(saveFoldername);

    std::string filenameStr = std::string(convertedStr, length);
    std::string foldernameStr = std::string(convertedFolderStr, lengthFolder);

    image::convertJpgToPng(filenameStr, foldernameStr);

    env->ReleaseStringUTFChars(filename, convertedStr);
  }
  catch(...)
  {
    rethrow_as_java_exception(env);
  }
}