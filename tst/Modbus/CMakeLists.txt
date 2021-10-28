# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(
    Boost 
    COMPONENTS program_options system unit_test_framework filesystem thread date_time chrono regex 
    REQUIRED
)

include_directories(
    ./
    ${PROJECT_BINARY_DIR}
    ${MODBUS_INSTALL_PREFIX}/usr/include/
    ../tst/Modbus
    ${Boost_INCLUDE_DIRS}
)

file(
    GLOB ModbusTest_SRC 
    ${PROJECT_SOURCE_DIR}/Modbus/unittest.cpp
    ${PROJECT_SOURCE_DIR}/Modbus/Modbus/*.cpp 
    ${PROJECT_SOURCE_DIR}/Modbus/unittest.cpp
)
add_executable(
    ModbusTest
    ${ModbusTest_SRC}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
    ModbusTest
    ${MODBUS_INSTALL_PREFIX}/usr/lib/libModbus.so
    ${CMAKE_DL_LIBS}
    ${pthread}
    ${Boost_LIBRARIES}
)
