# ================================================================
# 记事本项目 Qt 工程配置文件
# ================================================================
# 这是一个基于Qt框架开发的简单记事本应用程序的项目配置文件
# 定义了项目的编译设置、依赖模块、源文件等信息

# Qt模块配置
# core: Qt核心模块，提供基础类和功能
# gui: Qt图形用户界面模块，提供GUI相关类
QT       += core gui

# Qt版本兼容性配置
# 如果Qt主版本号大于4，则添加widgets模块
# widgets模块在Qt5+中独立出来，包含窗口部件类
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 编译器配置
# 启用C++11标准支持，使用现代C++特性
CONFIG += c++11

# 编译器警告配置
# 当使用已弃用的Qt功能时发出编译警告
# 具体警告内容取决于编译器类型
# 建议查阅Qt文档了解如何迁移弃用的API
DEFINES += QT_DEPRECATED_WARNINGS

# 可选：禁用弃用API的编译配置
# 取消注释下面的行可以让代码在使用弃用API时编译失败
# 可以选择性地禁用特定Qt版本之前的弃用API
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # 禁用Qt 6.0.0之前的所有弃用API

# 源文件列表
# 包含项目中所有的C++源文件(.cpp)
SOURCES += \
    main.cpp \          # 程序主入口文件
    mytextedit.cpp \    # 自定义文本编辑器实现
    widget.cpp          # 主窗口类实现

# 头文件列表
# 包含项目中所有的C++头文件(.h)
HEADERS += \
    mytextedit.h \      # 自定义文本编辑器类声明
    widget.h            # 主窗口类声明

# UI界面文件列表
# 包含Qt Designer设计的界面文件(.ui)
FORMS += \
    widget.ui           # 主窗口界面设计文件

# 部署配置
# 为不同平台设置默认的安装路径
qnx: target.path = /tmp/$${TARGET}/bin                    # QNX系统路径
else: unix:!android: target.path = /opt/$${TARGET}/bin   # Unix系统路径（除Android外）
!isEmpty(target.path): INSTALLS += target                # 如果路径非空则启用安装规则

# 资源文件配置
# 包含项目中的Qt资源文件(.qrc)
# 资源文件用于嵌入图标、图片等静态资源
RESOURCES += \
    res.qrc \
    res.qrc \
    res.qrc             # 项目资源文件

# 分发文件列表
# 用于指定需要包含在发布包中的额外文件
# 当前为空，可根据需要添加文档、许可证等文件
DISTFILES +=
