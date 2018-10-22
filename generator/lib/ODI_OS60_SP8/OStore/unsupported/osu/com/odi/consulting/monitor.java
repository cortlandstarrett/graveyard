package com.odi.consulting;
import java.lang.String;

public class Monitor {
    private static boolean _initialized = false;
    private static native void _initialize();
    private static native void _initializeAll();
    private static native void _log(String s);

    public static void initialize() {
	if (_initialized) {
	    _initialize();
	}
    }

    public static void initializeAll() {
	if (_initialized) {
	    _initializeAll();
	}
    }

    public static void log(String s) {
	if (_initialized) {
	    _log(s);
	}
    }

    static {
      try {
	  System.loadLibrary("osu6mon");
	  _initialized = true;
      } catch (java.lang.UnsatisfiedLinkError x) {
        x.printStackTrace();
        System.out.println("Error linking");
	  _initialized = false;
      }
    }
}
