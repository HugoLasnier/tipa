# Add include directories
include_directories (.)
include_directories (../../src)
include_directories (../../test)

set (TIPA_JSON_LIBRARY ${PROJECT_NAME}_json)
add_library (${TIPA_JSON_LIBRARY} ${JSON_LIBRARY} json.cpp)

set (EXECUTABLE_NAME main)
set (EXECUTABLE_SOURCES main.cpp)


# Create the executable.
add_executable (${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})

target_compile_features (${EXECUTABLE_NAME} PRIVATE cxx_range_for)

# Indicate that the executable needs tipalibrary.
target_link_libraries (${EXECUTABLE_NAME} ${TIPA_JSON_LIBRARY} ${PROJECT_NAME})
