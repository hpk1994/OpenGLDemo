package com.dianping.opengldemo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class OpenGlSurfaceView extends GLSurfaceView {
    private static final int OPENGL_ES_VERSION = 2;
    OpenGLRender mOpenGLRender;

    public OpenGlSurfaceView(Context context) {
        this(context,null);

    }

    public OpenGlSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initRender();
    }

    private void initRender() {
        mOpenGLRender = new OpenGLRender();
        setEGLContextClientVersion(OPENGL_ES_VERSION);
        setRenderer(mOpenGLRender);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }
}
