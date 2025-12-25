cmake_minimum_required(VERSION 3.16)
project(NeutronScattering)

if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置源代码
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(NeutronSca exe03N.cc ${sources})

target_link_libraries(NeutronSca ${Geant4_LIBRARIES})
