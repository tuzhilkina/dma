cmake_minimum_required(VERSION 3.12)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

if (NOT build_suffix)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin.${build_suffix})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.${build_suffix}.dbg)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.${build_suffix}.rel)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.${build_suffix}.relwithdbg)
endif()

set(CMAKE_MODULE_PATH 
  ${CMAKE_MODULE_PATH} 
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake 
  CACHE STRING "Modules for CMake" FORCE
)

project(dma)

add_subdirectory(address_sort)
add_subdirectory(adj_list)
add_subdirectory(adj_tree)
add_subdirectory(coherent_list)
add_subdirectory(coherent_tree)
add_subdirectory(combinatorics)
add_subdirectory(floid)
add_subdirectory(fragm)
add_subdirectory(tsp_genetic)