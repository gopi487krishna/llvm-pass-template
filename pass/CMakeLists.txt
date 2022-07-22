# Hardcode os path into OS_DIR for excluding files and directories by the pass

set(SOURCE_PATH ${CMAKE_SOURCE_DIR})
cmake_path(GET SOURCE_PATH PARENT_PATH OS_PATH)

add_library(StandardPass MODULE
    # List your source files here.
    pass.cpp
)


# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(StandardPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(MemoryPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
