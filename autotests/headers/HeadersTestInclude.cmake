set(REQUIRED_QT_VERSION "5.3.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Widgets Xml PrintSupport)
find_package(KF5 5.7.0 REQUIRED CoreAddons WidgetsAddons GuiAddons Config)
find_package(KPropertyWidgets REQUIRED)
find_package(KReport REQUIRED)
