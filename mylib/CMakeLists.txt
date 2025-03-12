project(mylib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    ${SOURCE_DIR}/engine.cpp
    ${SOURCE_DIR}/hero.cpp
    ${SOURCE_DIR}/boss.cpp
    ${SOURCE_DIR}/ennemie.cpp
    ${SOURCE_DIR}/ennemieBehavior.cpp
    ${SOURCE_DIR}/sceneManager.cpp
    ${SOURCE_DIR}/sceneBase.cpp
    ${SOURCE_DIR}/gameObject.cpp
    ${SOURCE_DIR}/pause.cpp
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/menu.cpp
    ${SOURCE_DIR}/state.cpp
    ${SOURCE_DIR}/heroState.cpp
    ${SOURCE_DIR}/behaviorTree.cpp
    ${SOURCE_DIR}/resourceManager.cpp
)

set(HEADERS
    ${HEADER_DIR}/engine.h
    ${HEADER_DIR}/hero.h
    ${HEADER_DIR}/boss.h
    ${HEADER_DIR}/ennemie.h
    ${HEADER_DIR}/ennemieBehavior.h
    ${HEADER_DIR}/sceneManager.h
    ${HEADER_DIR}/sceneBase.h
    ${HEADER_DIR}/gameObject.h
    ${HEADER_DIR}/game.h
    ${HEADER_DIR}/pause.h
    ${HEADER_DIR}/menu.h
    ${HEADER_DIR}/state.h
    ${HEADER_DIR}/heroState.h
    ${HEADER_DIR}/behaviorTree.h
    ${HEADER_DIR}/resourceManager.h
)

add_library(${PROJECT_NAME}
STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(mylib PUBLIC ${SFML_INCLUDE_DIR}) 
link_directories(${SFML_LIB_DIR})
target_link_libraries(${PROJECT_NAME}
PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

add_custom_command(TARGET mylib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_BIN_DIR} $<TARGET_FILE_DIR:mylib>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")