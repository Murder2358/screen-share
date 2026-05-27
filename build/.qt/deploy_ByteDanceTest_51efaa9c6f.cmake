include("D:/QTCode/ByteDanceTest/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ByteDanceTest-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "D:/QTCode/ByteDanceTest/build/ByteDanceTest.exe"
    GENERATE_QT_CONF
)
