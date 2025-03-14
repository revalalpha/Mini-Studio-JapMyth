project(ShootemUp)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Vérification si le dossier source est correct
message(STATUS "Looking for sources in: ${SOURCE_DIR}")

set(SOURCES
    ${SOURCE_DIR}/main.cpp
)

# Affiche la liste des fichiers trouvés
message(STATUS "Sources found: ${SOURCES}")

add_executable(ShootemUp ${SOURCES})

target_include_directories(ShootemUp PUBLIC ${SFML_INCLUDE_DIR}) 
link_directories(${SFML_LIB_DIR})

target_link_libraries(ShootemUp PUBLIC mylib PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_command(TARGET ShootemUp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_BIN_DIR} $<TARGET_FILE_DIR:ShootemUp>
)

set_target_properties(ShootemUp PROPERTIES FOLDER "Work")
