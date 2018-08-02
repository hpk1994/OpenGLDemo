cmake_minimum_required(VERSION 3.4.1)

add_library(opengl SHARED src/main/cpp/opengl.cpp )


find_library(GLESv1_CM-lib GLESv1_CM)
find_library(GLESv2-lib GLESv2)
find_library(dl-lib dl)
find_library(log-lib log)
find_library(android-lib android)
find_library(EGL-lib EGL)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(opengl
                      ${GLESv1_CM-lib}
                      ${GLESv2-lib}
                      ${dl-lib}
                      ${log-lib}
                      ${android-lib}
                      ${EGL-lib}
                      ${jnigraphics-lib})