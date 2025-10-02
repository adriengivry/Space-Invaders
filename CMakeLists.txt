cmake_minimum_required(VERSION 3.14)
project(SpaceInvaders C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Try to find SDL2 packages first
find_package(SDL2 QUIET)
find_package(SDL2_image QUIET)
find_package(SDL2_ttf QUIET)

# If not found, use FetchContent to download and build dependencies
if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found, will build from source")
    include(FetchContent)
    
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.5
        GIT_SHALLOW TRUE
    )
    
    set(SDL2_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SDL2)
    
    # Create SDL2::SDL2 and SDL2::SDL2main aliases
    if(NOT TARGET SDL2::SDL2)
        add_library(SDL2::SDL2 ALIAS SDL2)
    endif()
    if(NOT TARGET SDL2::SDL2main)
        add_library(SDL2::SDL2main ALIAS SDL2main)
    endif()
endif()

if(NOT SDL2_image_FOUND)
    message(STATUS "SDL2_image not found, will build from source")
    
    if(NOT COMMAND FetchContent_Declare)
        include(FetchContent)
    endif()
    
    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.2
        GIT_SHALLOW TRUE
        GIT_SUBMODULES "external/libpng" "external/zlib"  # Only fetch required submodules for PNG support
    )
    
    set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)
    set(SDL2IMAGE_PNG ON CACHE BOOL "" FORCE)
    set(SDL2IMAGE_PNG_SHARED OFF CACHE BOOL "" FORCE)
    
    # Disable all unnecessary formats
    set(SDL2IMAGE_AVIF OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_BMP ON CACHE BOOL "" FORCE)
    set(SDL2IMAGE_GIF OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_JPG OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_JXL OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_LBM OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_PCX OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_PNM OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_QOI OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_SVG OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_TGA OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_TIF OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_WEBP OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_XCF OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_XPM OFF CACHE BOOL "" FORCE)
    set(SDL2IMAGE_XV OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL2_image)
    
    # Create SDL2_image::SDL2_image alias
    if(NOT TARGET SDL2_image::SDL2_image)
        add_library(SDL2_image::SDL2_image ALIAS SDL2_image)
    endif()
endif()

if(NOT SDL2_ttf_FOUND)
    message(STATUS "SDL2_ttf not found, will build from source")
    
    if(NOT COMMAND FetchContent_Declare)
        include(FetchContent)
    endif()
    
    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.20.2
        GIT_SHALLOW TRUE
        GIT_SUBMODULES "external/freetype"  # Only fetch freetype submodule
    )
    
    set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
    set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)
    set(SDL2TTF_HARFBUZZ OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL2_ttf)
    
    # Create SDL2_ttf::SDL2_ttf alias
    if(NOT TARGET SDL2_ttf::SDL2_ttf)
        add_library(SDL2_ttf::SDL2_ttf ALIAS SDL2_ttf)
    endif()
endif()

# Source files
set(SOURCES
    src/main.c
    src/Game.c
    src/Window.c
    src/ImageManager.c
    src/Player.c
    src/Enemy.c
    src/Projectile.c
    src/EntityBody.c
    src/Text.c
    src/UserInterface.c
    src/int_to_alpha.c
    src/string_copy.c
    src/string_length.c
    src/string_concatenate.c
)

# Header files
set(HEADERS
    include/Game.h
    include/Window.h
    include/ImageManager.h
    include/Player.h
    include/Enemy.h
    include/Projectile.h
    include/EntityBody.h
    include/Text.h
    include/UserInterface.h
    include/int_to_alpha.h
    include/string_copy.h
    include/string_length.h
    include/string_concatenate.h
)

# Create executable
add_executable(SpaceInvaders ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(SpaceInvaders PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(SpaceInvaders PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)

# Copy resources to build directory
add_custom_command(TARGET SpaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:SpaceInvaders>/res
)
