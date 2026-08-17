cmake_minimum_required(VERSION 3.12)
project(TerminalGameEngine C)

# ============================================================================
# 1. COMPILER FLAGS & STANDARDS
# ============================================================================
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Strict warnings treated as errors
add_compile_options(-Wall -Wextra -Werror -pedantic)

# ============================================================================
# 2. DEPENDENCIES
# ============================================================================
find_package(Curses REQUIRED)

# ============================================================================
# 3. DYNAMICALLY DISCOVER EXISTING SOURCE FILES
# ============================================================================

# Automatically gather all existing .c files recursively
file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS "src/client/*.c")
file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS "src/server/*.c")
file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS "src/common/*.c")

# Filter out mainSNEW.c or temporary files from the server list if present
list(FILTER SERVER_SOURCES EXCLUDE REGEX ".*mainSNEW\\.c$")

# ============================================================================
# 4. GAME CLIENT TARGET
# ============================================================================
add_executable(game_client
    ${CLIENT_SOURCES}
    ${COMMON_SOURCES}
)

target_include_directories(game_client PRIVATE
    src
    src/common
    src/client
    src/client/snake
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(game_client PRIVATE
    ${CURSES_LIBRARIES}
)

# ============================================================================
# 5. GAME SERVER TARGET
# ============================================================================
add_executable(game_server
    ${SERVER_SOURCES}
    ${COMMON_SOURCES}
)

target_include_directories(game_server PRIVATE
    src
    src/common
    src/server
    src/server/snake
)