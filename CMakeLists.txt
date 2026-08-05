cmake_minimum_required(VERSION 3.10)
project(TerminalGameEngine C)

# Enable C99 standard and strict compiler warnings
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror -pedantic)

# Tell CMake where to look for .h headers
include_directories(src)

# Find ncurses for the client UI
find_package(Curses REQUIRED)

# ============================================================================
# 1. GATHER SOURCE FILES
# ============================================================================

# Code shared by BOTH Client and Server
file(GLOB COMMON_SOURCES "src/common/*.c")
file(GLOB GAME_SOURCES   "src/games/*.c")

# Code specific to Client or Server
file(GLOB CLIENT_SOURCES "src/client/*.c")
file(GLOB SERVER_SOURCES "src/server/*.c")


# ============================================================================
# 2. BUILD THE CLIENT EXECUTABLE
# ============================================================================

# game_client needs client code + game rules + shared protocol code
add_executable(game_client ${CLIENT_SOURCES} ${GAME_SOURCES} ${COMMON_SOURCES})

# Link ncurses ONLY to the client
target_link_libraries(game_client ${CURSES_LIBRARIES})


# ============================================================================
# 3. BUILD THE SERVER EXECUTABLE
# ============================================================================

# game_server needs server code + game rules + shared protocol code
add_executable(game_server ${SERVER_SOURCES} ${GAME_SOURCES} ${COMMON_SOURCES})

# (Optional) Link POSIX threads to server if using multi-threading
# find_package(Threads REQUIRED)
# target_link_libraries(game_server Threads::Threads)
