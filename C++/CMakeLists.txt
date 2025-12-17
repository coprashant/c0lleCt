cmake_minimum_required(VERSION 3.30)
project(c0lleCt)

set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(c0lleCt
        "D:/practice programs/c0lleCt/main.cpp"
        Game.cpp
        Basket.cpp
        Egg.cpp
)

# Set SFML directory
set(SFML_DIR "D:/Libraries/SFML-2.6.1/lib/cmake/SFML")

# Include SFML headers
include_directories("D:/Libraries/SFML-2.6.1/include")

# Find SFML components
find_package(SFML COMPONENTS graphics window system audio network REQUIRED)

# Link SFML libraries
if(SFML_STATIC_LIBRARIES)
    # Link SFML static libraries
    target_link_libraries(c0lleCt sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

    # Set static linking flags
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
else()
    # Link SFML dynamic libraries
    target_link_libraries(c0lleCt sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

    # Ensure the SFML DLLs are found at runtime
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    add_custom_command(TARGET c0lleCt POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${SFML_DIR}/../../../bin $<TARGET_FILE_DIR:c0lleCt>)
endif()

# Define the resource directory
set(RESOURCE_DIR "resources")

# Create a post-build command to copy the resource directory to the output directory
add_custom_command(TARGET c0lleCt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} $<TARGET_FILE_DIR:c0lleCt>/${RESOURCE_DIR})
