set(cmake_version 3.18.3)

cmake_minimum_required(VERSION ${cmake_version})

set(ProjectName "UDPClient")

project(${ProjectName} 
		VERSION 0.1.0
		LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/VersionHelper")
include(VersionInfoUtils)
m_generate_version_info_sources_by_project_name(MY_PROJECT_NAME ${ProjectName})
		
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_FRONTEND_VARIANT: ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /WX /permissive- /W4")
  elseif(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow")
endif()

set(INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/include
	)
set(HEADERS 
	${CMAKE_SOURCE_DIR}/include/UDPClient.h
	${CMAKE_SOURCE_DIR}/include/InstanceCounter.h
	${CMAKE_SOURCE_DIR}/include/SocketAddress.h
	${CMAKE_SOURCE_DIR}/include/CommonInclude.h
	)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/UDPClient.cpp
	${SOURCE_DIR}/SocketAddress.cpp
	)

include_directories("${INCLUDE_DIRS}" "${CMAKE_CURRENT_LIST_DIR}/fmt/include")

# Setup testing
enable_testing()
add_subdirectory(fmt)
add_subdirectory(googletest)
add_subdirectory(tests)

# Create application
add_executable("udpclient" ${SOURCES} ${HEADERS})
target_link_libraries("udpclient" PUBLIC versionInfo fmt)
