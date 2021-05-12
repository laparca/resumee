add_executable(resumee main.cc)
target_include_directories(resumee
    PRIVATE
        ${resumee_SOURCE_DIR}
)
target_link_libraries(resumee yaml-cpp)
