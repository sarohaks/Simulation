cmake_minimum_required (VERSION 2.6)
project(QPET)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib)


# The project version number.
#######################################################
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)


# add a target to generate API documentation with Doxygen
#######################################################
#find_package(Doxygen)
#option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})


#if(BUILD_DOCUMENTATION)
   # if(NOT DOXYGEN_FOUND)
     #   message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    #endif()

    #set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    #set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile)

   # configure_file(${doxyfile_in} ${doxyfile} @ONLY)

  # add_custom_target(doc
   #     COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
   #     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
  #      COMMENT "Generating API documentation with Doxygen"
 #     VERBATIM)

#   install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc)
#endif()
######################################################


# add geant4 with vis drivers
######################################################
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
# remember to compile geant4 with following flags -DGEANT4_USE_QT=ON -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_GDML=ON -DGEANT4_BUILD_MULTITHREADED=ON
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
# Include ROOT
######################################################
find_package(ROOT REQUIRED COMPONENTS RIO)
message(STATUS "ROOT version: ${ROOT_VERSION}")
if(ROOT_FOUND AND ROOT_VERSION VERSION_LESS "6.0")
    message(FATAL_ERROR "ROOT 6.0 is required")
endif()

include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIR})


# Create ROOT dictionaries 
######################################################
                        #REFLEX_GENERATE_DICTIONARY(QPETClasses include/Event.hh)
                      #          add_library(JPetMCClassesDict SHARED ${sources} JPetMCClasses.cxx)
                      #         set(libsuffix .so)
                #                set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
                #                set_target_properties(JPetMCClassesDict PROPERTIES ${ROOT_LIBRARY_PROPERTIES})
                #                target_link_libraries(JPetMCClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
                #
                ##include(${ROOT_USE_FILE}) -- below workaround library.so
                #list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/cmake)
                ##
                ##
ROOT_GENERATE_DICTIONARY(QPETClasses include/TrackTree.hh include/ChamberBox.hh include/CalorimeterBox.hh include/EventInfo.hh MODULE QPETClasses  LINKDEF LinkDef.h)
#---Create a shared library with geneated dictionary
add_library(QPETClassesDict SHARED  src/TrackTree.cc src/ChamberBox.cc src/CalorimeterBox.cc src/EventInfo.cc QPETClasses.cxx )
target_link_libraries(QPETClassesDict ${ROOT_LIBRARIES})
#install(TARGETS QPETClassesDict DESTINATION lib/)


set(QPET_SCRIPTS
  vis.mac
  )
foreach(_script ${EXAMPLEB3_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#---Create  a main program using the library
######################################################
add_executable(QPET QPET.cc ${sources} ${headers})
target_link_libraries(QPET ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} QPETClassesDict )



