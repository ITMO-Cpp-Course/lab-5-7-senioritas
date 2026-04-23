add_library(documents_core STATIC
        src/Document.cpp
        src/DocumentBuilder.cpp
        src/InvertedIndex.cpp
        include/lab5/documents/SearchServer.hpp
        include_directories (src/documents_core/include/lab5)
        src/SearchServer.cpp
)

target_link_libraries(documents_core PRIVATE project_warnings)
if (TARGET project_sanitizers)
    target_link_libraries(documents_core PRIVATE project_sanitizers)
endif ()

target_include_directories(documents_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
