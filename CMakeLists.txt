cmake_minimum_required(VERSION 3.0)
 
# Define project name
project(fishbot_motion_driver)
# 开启Debug模式
SET(CMAKE_BUILD_TYPE DEBUG)
# Python库
SET(BUILD_PYTHON_LIB ON)
SET(PYTHON_LIB_NAME "fishbot")


add_compile_options(-Werror)
add_compile_options(-Wall)
add_compile_options(-std=c++14)
# 消除boost的note
add_compile_options(-D=BOOST_BIND_GLOBAL_PLACEHOLDERS)


# 全部代码文件
file(GLOB_RECURSE FISHBOT_SRC "src/*.cpp")
# 全部测试文件
file(GLOB_RECURSE FISHBOT_TESTS "tests/*_test.cpp")
# 全部Python封装文件
file(GLOB_RECURSE FISHBOT_PYTHON "src/*_python.cpp")
#从全部代码文件中去除Python封装文件
list(REMOVE_ITEM FISHBOT_SRC ${FISHBOT_PYTHON})


#**************************************************查找依赖**********************************************#
find_package(Boost REQUIRED COMPONENTS thread)
if(NOT Boost_FOUND)
  message("NOT found Boost")
endif()

find_package(fish_protocol REQUIRED)
if(NOT fish_protocol_FOUND)
  message("NOT found fish_protocol ,Please install!")
endif()


# 添加头文件
include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)
#**************************************************查找依赖**********************************************#




#**************************************************C++动态库**********************************************#



# 添加动态库
add_library(${PROJECT_NAME} SHARED ${FISHBOT_SRC})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${Python3_LIBRARIES} fish_protocol)




#**************************************************C++动态库**********************************************#







#***********************************************编译PYTHON库********************************************#

if(${BUILD_PYTHON_LIB} MATCHES "ON")

find_package(Python3 COMPONENTS Interpreter  Development REQUIRED)
find_package(Boost REQUIRED COMPONENTS python)

include_directories(${Python3_INCLUDE_DIRS})

# 添加动态库
add_library(${PYTHON_LIB_NAME} SHARED ${FISHBOT_SRC} ${FISHBOT_PYTHON})
target_link_libraries(${PYTHON_LIB_NAME} 
  ${Boost_LIBRARIES} 
  ${Python3_LIBRARIES} 
  fish_protocol
)
endif()

#**************************************************编译PYTHON库*********************************************#



#**************************************************DEBUG模式-添加测试文件***************************************#
if(${CMAKE_BUILD_TYPE} MATCHES "DEBUG")

find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
  message("NOT found GTest")
endif()



# 添加测试可执行文件
add_executable(${PROJECT_NAME}_test  
    ${FISHBOT_TESTS}
    ${FISHBOT_SRC}
)

target_link_libraries(${PROJECT_NAME}_test
    ${Boost_LIBRARIES}
    gtest
    fish_protocol
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


endif()
#****************************************DEBUG模式-添加测试文件*********************************************#





#****************************************生成配置文件，安装到系统*********************************************#
install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${PROJECT_NAME}Config.cmake
        VERSION 1.0
        COMPATIBILITY AnyNewerVersion 
        )

install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
        )

#****************************************生成配置文件，安装到系统*********************************************#
