package com.dianping.opengldemo;

public class OpenGLJni {
    static {
        try {
            System.loadLibrary("opengl");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static native void initOpenGL();

    public static native void render();
}
