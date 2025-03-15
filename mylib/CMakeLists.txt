project(mylib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    ${SOURCE_DIR}/Animation.cpp
    ${SOURCE_DIR}/AnimationManager.cpp
    ${SOURCE_DIR}/Barrier.cpp
    ${SOURCE_DIR}/Boss.cpp
    ${SOURCE_DIR}/BossBehavior.cpp
    ${SOURCE_DIR}/Game.cpp
    ${SOURCE_DIR}/GameScene.cpp
    ${SOURCE_DIR}/HealthComponent.cpp
    ${SOURCE_DIR}/Hero.cpp
    ${SOURCE_DIR}/HeroState.cpp
    ${SOURCE_DIR}/IComponent.cpp
    ${SOURCE_DIR}/IGameObject.cpp
    ${SOURCE_DIR}/MovementComponent.cpp
    ${SOURCE_DIR}/MyMath.cpp
    ${SOURCE_DIR}/PauseScene.cpp
    ${SOURCE_DIR}/SceneManager.cpp
    ${SOURCE_DIR}/StateComponent.cpp
    ${SOURCE_DIR}/TextureCache.cpp
    ${SOURCE_DIR}/TitleScene.cpp
    ${SOURCE_DIR}/Tree.cpp
    ${SOURCE_DIR}/State.cpp
    ${SOURCE_DIR}/StateMachine.cpp

)

set(HEADERS
    ${HEADER_DIR}/Animation.h
    ${HEADER_DIR}/AnimationManager.h
    ${HEADER_DIR}/Barrier.h
    ${HEADER_DIR}/Boss.h
    ${HEADER_DIR}/BossBehavior.h
    ${HEADER_DIR}/Game.h
    ${HEADER_DIR}/GameScene.h
    ${HEADER_DIR}/HealthComponent.h
    ${HEADER_DIR}/Hero.h
    ${HEADER_DIR}/HeroState.h
    ${HEADER_DIR}/IComponent.h
    ${HEADER_DIR}/IGameObject.h
    ${HEADER_DIR}/MovementComponent.h
    ${HEADER_DIR}/MyMath.h
    ${HEADER_DIR}/PauseScene.h
    ${HEADER_DIR}/SceneManager.h
    ${HEADER_DIR}/StateComponent.h
    ${HEADER_DIR}/TextureCache.h
    ${HEADER_DIR}/TitleScene.h
    ${HEADER_DIR}/Tree.h
    ${HEADER_DIR}/State.h
    ${HEADER_DIR}/StateMachine.h

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