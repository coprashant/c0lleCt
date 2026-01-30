cmake_minimum_required(VERSION 3.10)
project(c0lleCt)

# Standard C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. SFML SETUP 
set(SFML_DIR "D:/Libraries/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)

# 2. BUILD THE EXE
add_executable(c0lleCt
    main.cpp
    Game.cpp
    Basket.cpp
    Egg.cpp
)

# 3. LINKING

target_link_libraries(c0lleCt sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

# 4. DEPLOYMENT OF ASSETS AND DLLs

add_custom_command(TARGET c0lleCt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "D:/Libraries/SFML-2.6.1/bin"
    "$<TARGET_FILE_DIR:c0lleCt>"
    COMMENT "Moving DLLs to the build folder..."
)

add_custom_command(TARGET c0lleCt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:c0lleCt>/resources"
    COMMENT "Moving images/sounds to the build folder..."
)