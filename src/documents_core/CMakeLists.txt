add_library(documents_core STATIC
        src/Document.cpp
        src/DocumentBuilder.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
)

# Указываем пути к заголовочным файлам
target_include_directories(documents_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}           # чтобы можно было писать #include "lab5/documents/Document.hpp"
        ${CMAKE_CURRENT_SOURCE_DIR}/include   # если там что-то есть
)

target_link_libraries(documents_core PRIVATE project_warnings)

if (TARGET project_sanitizers)
    target_link_libraries(documents_core PRIVATE project_sanitizers)
endif ()