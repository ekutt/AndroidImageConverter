package com.ekutt.example.imageconverter;

public class ImageConverter {
  static {
    System.loadLibrary("imageOps-jni");
  }
  
  private static native void convertJPEGtoTIFF_Native(String filename, String foldername);

  public static void convertJPEGtoTIFF(String filename, String foldername)
  {
    ImageConverter.convertJPEGtoTIFF_Native(filename, foldername);
  }
}
