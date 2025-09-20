#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>

/**
 * @brief MyTextEdit类 - 自定义文本编辑器
 * 
 * 继承自QTextEdit，扩展了以下功能：
 * 1. 支持Ctrl+鼠标滚轮进行字体缩放
 * 2. 跟踪Ctrl键的按下和释放状态
 * 3. 提供更好的用户交互体验
 * 
 * 主要用于实现类似现代文本编辑器的缩放功能
 */
class MyTextEdit : public QTextEdit
{
public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，用于建立Qt对象层次结构
     * 
     * Qt的父子对象机制说明：
     * - 父对象负责管理子对象的生命周期
     * - 当父对象被销毁时，所有子对象会自动被销毁
     * - 子对象会自动添加到父对象的布局中
     * - 这种机制简化了内存管理和界面布局
     */
    MyTextEdit(QWidget *parent);
    
protected:
    /**
     * @brief 鼠标滚轮事件处理函数
     * @param e 滚轮事件对象，包含滚动方向和距离信息
     * 
     * 重写此函数以实现：
     * - 检测Ctrl键是否被按下
     * - 根据滚轮方向进行字体放大或缩小
     * - 阻止默认的滚动行为（当Ctrl被按下时）
     */
    void wheelEvent(QWheelEvent *e) override;
    
    /**
     * @brief 键盘按下事件处理函数
     * @param e 键盘事件对象，包含按键信息
     * 
     * 用于检测Ctrl键的按下状态，更新内部状态变量
     * 为后续的滚轮事件处理提供状态信息
     */
    void keyPressEvent(QKeyEvent *e) override;
    
    /**
     * @brief 键盘释放事件处理函数
     * @param e 键盘事件对象，包含释放的按键信息
     * 
     * 用于检测Ctrl键的释放状态，及时更新内部状态
     * 确保状态跟踪的准确性
     */
    void keyReleaseEvent(QKeyEvent *e) override;
    
private:
    /**
     * @brief Ctrl键状态标志
     * 
     * 用于跟踪Ctrl键是否处于按下状态：
     * - true: Ctrl键当前被按下
     * - false: Ctrl键当前未被按下
     * 
     * 这个状态用于判断是否应该响应滚轮缩放操作
     */
    bool ctrlKeyPressed = false;
};

#endif // MYTEXTEDIT_H
