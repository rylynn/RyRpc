cmake_minimum_required(VERSION 3.0)
project(rynrpc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -DHAVE_KQUEUE -std=c++11")
#add_definitions("-DHAVE_KQUEUE -O2 -std=c++11")

SET("/usr/local/Cellar/boost/1.64.0_1" BOOST_PATH)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/net DIR_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/common DIR_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SRC)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
link_directories(/usr/local/Cellar/glog/0.3.5_1/lib)

include_directories(${BOOST_PATH}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/net)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
include_directories(/usr/local/Cellar/glog/0.3.5_1/include)
link_directories(${BOOST_PATH}/lib)

#add_library(rynrpc STATIC ${CMAKE_CURRENT_SOURCE_DIR} ${NET_SRCS} ${COMMON_SRCS})
add_executable(test_svr main.cpp ${DIR_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/common/switch_ctx.o)
 #${CMAKE_CURRENT_SOURCE_DIR}/common/switch_ctx.o
target_link_libraries(test_svr glog)
