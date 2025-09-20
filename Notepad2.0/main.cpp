/**
 * @file main.cpp
 * @brief 记事本应用程序的主入口文件
 * 
 * 这是一个基于Qt框架开发的简单记事本应用程序
 * 提供了基本的文本编辑功能，包括文件操作、字体缩放、
 * 编码支持等特性
 */

#include "widget.h"      // 主窗口类头文件
#include <QApplication>   // Qt应用程序类

/**
 * @brief 程序主入口函数
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 程序退出状态码
 * 
 * 程序执行流程：
 * 1. 创建QApplication对象，初始化Qt应用程序环境
 * 2. 创建主窗口Widget对象
 * 3. 显示主窗口
 * 4. 进入Qt事件循环，等待用户交互
 * 5. 当用户关闭程序时，返回退出状态码
 */
int main(int argc, char *argv[])
{
    // 创建Qt应用程序对象
    // 这是所有Qt GUI应用程序的必需步骤
    // argc和argv用于处理命令行参数
    QApplication a(argc, argv);
    
    // 创建主窗口对象
    // Widget类包含了记事本的所有功能实现
    Widget w;
    
    // 显示主窗口
    // 调用show()方法使窗口可见
    w.show();
    
    // 启动Qt事件循环
    // exec()会阻塞程序执行，直到应用程序退出
    // 在事件循环中处理用户输入、窗口重绘等事件
    // 返回值通常为0表示正常退出
    return a.exec();
}
