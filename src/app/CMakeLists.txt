
# Add all the source files in src
file(GLOB SOURCES "*.cpp" "*.h" "*.hpp")

# Create a library target for src
add_library(SrcAppSupportTarget ${SOURCES})
