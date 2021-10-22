# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# prebuild
#
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaModbusServer/Build/BuildConfig.h.in"
    "${PROJECT_BINARY_DIR}/BuildConfig.h"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaModbusServer/linux/etc/init/OpcUaModbusServer.conf.in"
    "${PROJECT_BINARY_DIR}/OpcUaModbusServer.conf"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaModbusServer/linux/etc/init.d/OpcUaModbusServer.in"
    "${PROJECT_BINARY_DIR}/OpcUaModbusServer"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/OpcUaModbusServer/linux/usr/lib/systemd/system/OpcUaModbusServer.service.in"
    "${PROJECT_BINARY_DIR}/OpcUaModbusServer.service"
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
include_directories(
    ${OPCUASTACK_INSTALL_PREFIX}/usr/include/OpcUaStack${OPCUASTACK_VERSION_MAJOR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

file(
    GLOB 
    OpcUaModbusServer_SRC 
    ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/*/*.cpp
)

add_library(
    OpcUaModbusServer SHARED
    ${OpcUaModbusServer_SRC}
)

target_link_libraries(
    OpcUaModbusServer
    ${pthread}
    ${OPCUASTACK_LIBRARY_CORE}
    ${OPCUASTACK_LIBRARY_CLIENT}
    ${OPCUASTACK_LIBRARY_SERVER}
    ${OPCUASTACK_LIBRARY_PUBSUB}
    ${Boost_LIBRARIES}
)

if (WIN32)
    target_link_libraries(OpcUaModbusServer wsock32 ws2_32)

    if (MINGW)
        set(CMAKE_SHARED_LIBRARY_PREFIX "")
    endif()
endif()

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

file (GLOB CONFIG_FILES ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/Config/*.xml)
install(TARGETS OpcUaModbusServer DESTINATION ${INSTALL_PREFIX}/lib)

if (WIN32)
    install(FILES ${CONFIG_FILES} DESTINATION ${INSTALL_PREFIX}/../etc/OpcUaStack/OpcUaModbusServer) 
    install(FILES ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/linux/log/README DESTINATION ${INSTALL_PREFIX}/../var/log/OpcUaStack/OpcUaModbusServer)
    install(DIRECTORY DESTINATION ${INSTALL_PREFIX}/../var/log/OpcUaStack/OpcUaModbusServer)
else()    
    install(FILES ${CONFIG_FILES} DESTINATION ${INSTALL_PREFIX}/../etc/OpcUaStack/OpcUaModbusServer) 
    install(FILES ${PROJECT_SOURCE_DIR}/OpcUaModbusServer/linux/log/README DESTINATION /var/log/OpcUaStack/OpcUaModbusServer)
    install(DIRECTORY DESTINATION /var/log/OpcUaStack/OpcUaModbusServer)

    install(PROGRAMS ${PROJECT_BINARY_DIR}/OpcUaModbusServer DESTINATION /etc/init.d)
    install(FILES ${PROJECT_BINARY_DIR}/OpcUaModbusServer.conf DESTINATION /etc/init)
    install(FILES ${PROJECT_BINARY_DIR}/OpcUaModbusServer.service DESTINATION /usr/lib/systemd/system)
endif()

if (CPACK_BINARY_DEB)
    set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaModbusServer/linux/script/postinst"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaModbusServer/linux/script/preinst"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaModbusServer/linux/script/prerm"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/OpcUaModbusServer/linux/script/postrm")
endif()

if (CPACK_BINARY_RPM)
    set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OpcUaModbusServer/linux/script/postinst)
    set(CPACK_RPM_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OpcUaModbusServer/linux/script/prerm)
endif()
