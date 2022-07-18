cmake_minimum_required(VERSION 3.0)
 
# Define project name
project(fishbot_motion_sdk)

add_compile_options(-Werror)
add_compile_options(-Wall)
add_compile_options(-std=c++14)
# 消除boost的note
add_compile_options(-D=BOOST_BIND_GLOBAL_PLACEHOLDERS)
# 开启Debug模式
SET(CMAKE_BUILD_TYPE DEBUG)

# 添加头文件
include_directories(
    include
    ${Boost_INCLUDE_DIRS}
)

# 添加代码文件
file(GLOB_RECURSE FISHBOT_SRC "src/*.cpp")
file(GLOB_RECURSE FISHBOT_MAIN_SRC "src/main.cpp")
# 添加测试文件
file(GLOB_RECURSE FISHBOT_TESTS "src/*_test.cpp")
# 从资源文件中移除所有的单元测试文件
list(REMOVE_ITEM FISHBOT_SRC ${FISHBOT_TESTS})
# 测试所需资源文件
file(GLOB_RECURSE FISHBOT_TEST_SRC "src/*.cpp")
list(REMOVE_ITEM FISHBOT_TEST_SRC ${FISHBOT_MAIN_SRC})
# 库文件
file(GLOB_RECURSE FISHBOT_LIB_SRC "src/*.cpp")
list(REMOVE_ITEM FISHBOT_LIB_SRC ${FISHBOT_MAIN_SRC} ${FISHBOT_TESTS})

# 查找依赖
find_package(Boost REQUIRED COMPONENTS thread)
if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()
find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
    message("NOT found GTest")
endif()

# 添加动态库
add_library(${PROJECT_NAME} SHARED ${FISHBOT_LIB_SRC})

# 添加可执行文件
add_executable(${PROJECT_NAME}_main  ${FISHBOT_SRC})
target_link_libraries(${PROJECT_NAME}_main ${Boost_LIBRARIES})

# 添加测试可执行文件
add_executable(${PROJECT_NAME}_test  
    ${FISHBOT_TESTS}
    ${FISHBOT_TEST_SRC}
)
target_link_libraries(${PROJECT_NAME}_test
    ${Boost_LIBRARIES}
    gtest
)


# 代码格式检查
set(CPPLINT_SRC ${FISHBOT_SRC} ${FISHBOT_TESTS})
list(REMOVE_DUPLICATES CPPLINT_SRC)
foreach(v ${CPPLINT_SRC})
  execute_process(
    COMMAND cpplint --quiet ${v}
    ERROR_VARIABLE _result
  )
  if( _result)
    message(FATAL "cpplint check failed!  \n ${_result}")
  endif()
endforeach(v)
