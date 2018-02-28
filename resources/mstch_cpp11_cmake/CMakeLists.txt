# Copyright 2016, alex at staticlibs.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

project ( mstch_cpp11 CXX )

if ( NOT DEFINED ${PROJECT_NAME}_SOURCES_DIR )
    set ( ${PROJECT_NAME}_SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../mstch_cpp11 CACHE INTERNAL "" )
endif ( )

# check deplibs cache
if ( STATICLIB_USE_DEPLIBS_CACHE )
    set ( ${PROJECT_NAME}_CACHED_LIB_PATH ${STATICLIB_DEPLIBS_CACHE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX} )
    if ( EXISTS ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        add_library( ${PROJECT_NAME} STATIC IMPORTED GLOBAL )
        set_target_properties( ${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        message ( STATUS "Using cached library: [${${PROJECT_NAME}_CACHED_LIB_PATH}]" )
        return ( )
    endif ( )
endif ( )

add_library ( ${PROJECT_NAME} STATIC 
        ${${PROJECT_NAME}_SOURCES_DIR}/src/mstch.cpp
        ${${PROJECT_NAME}_SOURCES_DIR}/src/render_context.cpp 
        ${${PROJECT_NAME}_SOURCES_DIR}/src/template_type.cpp 
        ${${PROJECT_NAME}_SOURCES_DIR}/src/token.cpp 
        ${${PROJECT_NAME}_SOURCES_DIR}/src/utils.cpp 
        ${${PROJECT_NAME}_SOURCES_DIR}/src/state/in_section.cpp 
        ${${PROJECT_NAME}_SOURCES_DIR}/src/state/outside_section.cpp
        ${${PROJECT_NAME}_SOURCES_DIR}/include/mstch/mstch.hpp
        ${${PROJECT_NAME}_SOURCES_DIR}/include/mstch/mstch_node.hpp )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE 
        ${${PROJECT_NAME}_SOURCES_DIR}/include
        ${${PROJECT_NAME}_SOURCES_DIR}/src )
        
if ( ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )
    target_compile_options ( ${PROJECT_NAME} PRIVATE
            /wd4512 /wd4706 )
endif ( )         
