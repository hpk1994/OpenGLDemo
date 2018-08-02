#include <jni.h>
#include <GLES2/gl2.h>


extern "C" {

GLuint d_glprogram = 0;

JNIEXPORT void JNICALL Java_com_dianping_opengldemo_OpenGLJni_initOpenGL(JNIEnv *env, jclass obj) {
    GLuint glProgram;

    //清除屏幕颜色
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    //============================顶点着色器================================

    //vertex 顶点着色器代码
    const char *shader_vertex_code = "uniform mediump mat4 MODELVIEWPROJECTIONMATRIX;\n"
            "attribute vec4 POSITION;\n"
            "void main(){\n"
            "  gl_Position = POSITION;\n"
            "}";


    //创建了着色器返回一个句柄
    GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    //判断是否创建成功
    if (vertexShaderHandle == 0) {
        return;
    }


    //通过着色器句柄连接着色器内容
    glShaderSource(vertexShaderHandle, 1, &shader_vertex_code, NULL);
    //编译着色器
    glCompileShader(vertexShaderHandle);

    //验证编译结果
    GLint vertexCompileResult;
    glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &vertexCompileResult);
    if (vertexCompileResult == GL_FALSE) {
        glDeleteShader(vertexShaderHandle);
        return;
    }


    //============================片段着色器================================

    //vertex 片段着色器代码
    const char *shader_fragment_code = "precision mediump float;\n"
            "void main(){\n"
            "   gl_FragColor = vec4(0,0,1,1);\n"
            "}";


    //创建了着色器返回一个句柄
    GLuint fragmentShaderhandle = glCreateShader(GL_FRAGMENT_SHADER);
    //判断是否创建成功
    if (fragmentShaderhandle == 0) {
        return;
    }

    //通过着色器句柄连接着色器内容
    glShaderSource(fragmentShaderhandle, 1, &shader_fragment_code, NULL);
    //编译着色器
    glCompileShader(fragmentShaderhandle);

    //验证编译结果
    GLint fragmentCompileResult;
    glGetShaderiv(fragmentShaderhandle, GL_COMPILE_STATUS, &fragmentCompileResult);

    if (fragmentCompileResult == GL_FALSE) {
        glDeleteShader(fragmentShaderhandle);
        return;
    }

    //============================链接OpenGL程序================================

    // 创建 OpenGL 程序返回一个句柄
    glProgram = glCreateProgram();

    if (glProgram == 0) {
        return;
    }

    // 链接上顶点着色器
    glAttachShader(glProgram, vertexShaderHandle);
    // 链接上片段着色器
    glAttachShader(glProgram, fragmentShaderhandle);
    // 链接着色器之后，链接OpenGL程序
    glLinkProgram(glProgram);

    // 验证链接结果是否失败
    GLint linkResult;
    glGetProgramiv(glProgram, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE) {
        glDeleteProgram(glProgram);
        return;
    }

    //============================验证OpenGL程序================================

    //验证OpenGl程序
    glValidateProgram(glProgram);
    GLint validateResult;
    glGetProgramiv(glProgram, GL_VALIDATE_STATUS, &validateResult);
    if (validateResult == GL_FALSE) {
        return;
    }

    d_glprogram = glProgram;

}


JNIEXPORT void JNICALL Java_com_dianping_opengldemo_OpenGLJni_render(JNIEnv *env, jclass obj) {

    //============================使用OpenGL程序================================

    //清除缓存
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //顶点数据
    GLfloat vertexs[] = {
            0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
    };

    //通过句柄使用OpenGL程序
    glUseProgram(d_glprogram);
    //给顶点着色器中的变量赋值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertexs);
    //默认情况下顶点着色器的属性（Attribute）变量都是关闭的，意味着数据在着色器端是不可见的。开启后可在顶点着色器中访问顶点的属性数据
    glEnableVertexAttribArray(0);
    //执行绘制 绘制方式 从数组缓存中的哪一位开始绘制,一般为0 数组中顶点的数量
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
}


