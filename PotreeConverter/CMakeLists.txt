project(PotreeConverter)

set(RAPIDJSON_INCLUDE_DIR lib/rapidjson/include)
set(ARGUMENTS_INCLUDE_DIR lib/arguments)

file(GLOB_RECURSE files src/*.cpp include/*.h include/*.hpp )
file(GLOB_RECURSE lib_rapidjson_files ${RAPIDJSON_INCLUDE_DIR}/* )
file(GLOB_RECURSE lib_argument_files ${ARGUMENTS_INCLUDE_DIR}/* )

include_directories(include ${LASZIP_INCLUDE_DIRS})
include_directories(include ${RAPIDJSON_INCLUDE_DIR})
include_directories(include ${ARGUMENTS_INCLUDE_DIR})
# If we install Boost through Homebrew, it will go here.
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

SOURCE_GROUP("Header Files\\io" FILES
	include/BINPointReader.hpp
	include/BINPointWriter.hpp
	include/LASPointReader.h
	include/LASPointWriter.hpp
	include/PlyPointReader.h
	include/PointReader.h
	include/PointWriter.hpp
	include/PTXPointReader.h
	include/XYZPointReader.hpp
)

SOURCE_GROUP("Source Files\\io" FILES
	src/BINPointReader.cpp
	src/LASPointReader.cpp
	src/LASPointWriter.cpp
	src/PTXPointReader.cpp
)

SOURCE_GROUP("lib\\rapidjson" FILES ${lib_rapidjson_files})
SOURCE_GROUP("lib\\arguments" FILES ${lib_argument_files})

add_executable(PotreeConverter ${files} ${lib_rapidjson_files} ${lib_argument_files})

target_link_libraries(PotreeConverter ${LASZIP_LIBRARY})

if(APPLE)
    find_package(Boost COMPONENTS system filesystem regex REQUIRED)
    # re: -DBOOST_NO_CX11_SCOPED_ENUMS, see https://stackoverflow.com/questions/35007134/c-boost-undefined-reference-to-boostfilesystemdetailcopy-file
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -pthread -lstdc++ -lm -DBOOST_NO_CXX11_SCOPED_ENUMS")
    target_link_libraries(PotreeConverter
      ${Boost_FILESYSTEM_LIBRARY}
      ${Boost_SYSTEM_LIBRARY}
      ${Boost_REGEX_LIBRARY}
      )
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pthread -lstdc++ -lm")
    target_link_libraries(PotreeConverter -lstdc++fs)
endif()

install(TARGETS PotreeConverter RUNTIME DESTINATION bin/ )
