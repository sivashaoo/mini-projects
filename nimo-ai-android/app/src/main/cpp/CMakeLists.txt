cmake_minimum_required(VERSION 3.22.1)
project(nimo_native LANGUAGES C CXX)

include(FetchContent)
set(LLAMA_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LLAMA_BUILD_SERVER OFF CACHE BOOL "" FORCE)
set(LLAMA_CURL OFF CACHE BOOL "" FORCE)
set(GGML_OPENMP OFF CACHE BOOL "" FORCE)
set(GGML_LLAMAFILE OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  llama_cpp
  GIT_REPOSITORY https://github.com/ggml-org/llama.cpp.git
  GIT_TAG b4510
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(llama_cpp)

add_library(nimo_native SHARED native.cpp)
target_compile_features(nimo_native PRIVATE cxx_std_17)
target_link_libraries(nimo_native PRIVATE llama log android)
