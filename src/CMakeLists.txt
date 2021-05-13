add_executable(resumee main.cc)
target_include_directories(resumee
    PRIVATE
        ${resumee_SOURCE_DIR}/src
)
target_link_libraries(resumee yaml-cpp)
