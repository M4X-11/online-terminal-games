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
# 3. DYNAMICALLY DISCOVER SOURCE FILES
# ============================================================================

# Engine & Common sources
file(GLOB_RECURSE CLIENT_ENGINE_SOURCES CONFIGURE_DEPENDS "src/client/*.c")
file(GLOB_RECURSE SERVER_ENGINE_SOURCES CONFIGURE_DEPENDS "src/server/*.c")
file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS "src/common/*.c")

# Game sources (Gathers from games/ and any future game subfolders!)
file(GLOB_RECURSE GAME_CLIENT_SOURCES CONFIGURE_DEPENDS "games/*/client/*.c")
file(GLOB_RECURSE GAME_SERVER_SOURCES CONFIGURE_DEPENDS "games/*/server/*.c")
file(GLOB_RECURSE GAME_COMMON_SOURCES CONFIGURE_DEPENDS "games/*/common/*.c")

# Filter out mainSNEW.c or temporary files from the server list if present
list(FILTER SERVER_ENGINE_SOURCES EXCLUDE REGEX ".*mainSNEW\\.c$")
list(FILTER SERVER_ENGINE_SOURCES
    EXCLUDE REGEX ".*/src/server/test-game/.*\\.c$"
)
list(FILTER SERVER_ENGINE_SOURCES
    EXCLUDE REGEX ".*/src/server/snake/.*\\.c$"
)

# Combine engine files + game files
set(ALL_CLIENT_SOURCES ${CLIENT_ENGINE_SOURCES} ${GAME_CLIENT_SOURCES} ${COMMON_SOURCES} ${GAME_COMMON_SOURCES})
set(ALL_SERVER_SOURCES ${SERVER_ENGINE_SOURCES} ${GAME_SERVER_SOURCES} ${COMMON_SOURCES} ${GAME_COMMON_SOURCES})

# ============================================================================
# 4. GAME CLIENT TARGET
# ============================================================================
add_executable(game_client
    ${ALL_CLIENT_SOURCES}
)

target_include_directories(game_client PRIVATE
    src
    games
    ${CURSES_INCLUDE_DIR}
)

target_link_libraries(game_client PRIVATE
    ${CURSES_LIBRARIES}
    m
)

# ============================================================================
# 5. GAME SERVER TARGET
# ============================================================================
add_executable(game_server
    ${ALL_SERVER_SOURCES}
)

target_include_directories(game_server PRIVATE
    src
    games
)

target_link_libraries(game_server PRIVATE
    m
)