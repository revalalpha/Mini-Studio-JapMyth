project(mylib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    ${SOURCE_DIR}/Animation.cpp
    ${SOURCE_DIR}/Barrier.cpp
    ${SOURCE_DIR}/Boss1.cpp
    ${SOURCE_DIR}/Game.cpp
    ${SOURCE_DIR}/GameCollision.cpp
    ${SOURCE_DIR}/GameScene.cpp
    ${SOURCE_DIR}/IGameObject.cpp
    ${SOURCE_DIR}/Inugami.cpp
    ${SOURCE_DIR}/IScene.cpp
    ${SOURCE_DIR}/Kappa.cpp
    ${SOURCE_DIR}/MyMath.cpp
    ${SOURCE_DIR}/OrbitalProjectile.cpp
    ${SOURCE_DIR}/PauseScene.cpp
    ${SOURCE_DIR}/PlayerShip.cpp
    ${SOURCE_DIR}/Projectile.cpp
    ${SOURCE_DIR}/Samurai.cpp
    ${SOURCE_DIR}/SceneManager.cpp
    ${SOURCE_DIR}/TextureCache.cpp
    ${SOURCE_DIR}/TitleScene.cpp
    ${SOURCE_DIR}/Tree.cpp
)

set(HEADERS
    ${HEADER_DIR}/Animation.h
    ${HEADER_DIR}/Barrier.h
    ${HEADER_DIR}/Boss1.h
    ${HEADER_DIR}/Game.h
    ${HEADER_DIR}/IGameObject.h
    ${HEADER_DIR}/Inugami.h
    ${HEADER_DIR}/IScene.h
    ${HEADER_DIR}/Kappa.h
    ${HEADER_DIR}/MyMath.h
    ${HEADER_DIR}/OrbitalProjectile.h
    ${HEADER_DIR}/PauseScene.h
    ${HEADER_DIR}/PlayerShip.h
    ${HEADER_DIR}/Projectile.h
    ${HEADER_DIR}/Samurai.h
    ${HEADER_DIR}/SceneManager.h
    ${HEADER_DIR}/TextureCache.h
    ${HEADER_DIR}/TitleScene.h
    ${HEADER_DIR}/Tree.h
    ${HEADER_DIR}/Boss1Behavior.h
    ${HEADER_DIR}/InugamiBehavior.h
    ${HEADER_DIR}/KappaBehavior.h
    ${HEADER_DIR}/SamuraiBehavior.h
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