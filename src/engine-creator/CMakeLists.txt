make_executable()

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    )

    include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
    link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild)
    
target_link_libraries(${PROJECT}
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
    ${IMGUI_LIBRARIES}
    pthread
    gmock
    gtest
    )

    #target_link_libraries(test pthread)
    #target_link_libraries(test gmock)
    #target_link_libraries(test gtest)