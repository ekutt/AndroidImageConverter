package com.ekutt.example.imageconverter;

public class ImageConverter {
  static {
    System.loadLibrary("imageOps-jni");
  }

  public static void convertJPEGtoPNG(String filename, String foldername)
  {
    ImageConverter.convertJPEGtoPNG_Native(filename, foldername);
  }

  private static native void convertJPEGtoPNG_Native(String filename, String foldername);
}
