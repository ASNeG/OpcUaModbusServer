# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

file(
    GLOB 
    Modbus_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/Modbus/*/*.cpp
)

add_library(
    Modbus SHARED
    ${Modbus_SRC}
)

target_link_libraries(
    Modbus
    ${pthread}
    ${Boost_LIBRARIES}
)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
install(
    TARGETS Modbus 
    DESTINATION ${INSTALL_PREFIX}/lib
)

file(GLOB INC_Modbus_Modbus ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/Modbus/Modbus/*.h)
install(
    FILES ${INC_Modbus_Modbus} 
    DESTINATION ${INSTALL_PREFIX}/include/Modbus/Modbus
    COMPONENT headers
)

file(GLOB INC_Modbus_Utility ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/Modbus/Utility/*.h)
install(
    FILES ${INC_Modbus_Utility} 
    DESTINATION ${INSTALL_PREFIX}/include/Modbus/Utility
    COMPONENT headers
)

