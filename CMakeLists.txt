cmake_minimum_required(VERSION 3.22)
project(university_management_system)

# Add source files
set(SOURCE_FILES main.c)
set(MYSQL_LINK_FLAGS -L/usr/lib/aarch64-linux-gnu -lmysqlclient -lzstd -lssl -lcrypto -lresolv -lm)

# Add executable target
add_executable(university_management_system ${SOURCE_FILES})

# Include directories if necessary
include_directories(libs /usr/include/mysql)

# add_library(logger libs/logger.c)

# Add compile definitions if necessary
# add_definitions(-DENABLE_FEATURE_X)

# Link libraries if necessary
target_link_libraries(university_management_system ${MYSQL_LINK_FLAGS})

# Set compiler flags if necessary
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Set build output directory if desired
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
