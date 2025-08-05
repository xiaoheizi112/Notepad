#include "mytextedit.h"

#include <QWheelEvent>
#include <QDebug>

/**
 * @brief MyTextEdit构造函数
 * @param parent 父窗口指针
 * 
 * 调用父类QTextEdit的构造函数进行初始化
 * 建立正确的Qt对象层次结构
 */
MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent)
{
    // 构造函数体为空，所有初始化通过成员初始化列表完成
    // ctrlKeyPressed已在头文件中初始化为false
}

/**
 * @brief 鼠标滚轮事件处理函数
 * @param e 滚轮事件对象
 * 
 * 实现Ctrl+滚轮的字体缩放功能
 * 注意：当前实现被注释掉了，可能是为了使用事件过滤器方式实现
 */
void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    // 以下代码被注释，展示了直接在wheelEvent中实现缩放的方法
    // 实际项目中使用了事件过滤器的方式来实现相同功能
    
//    // angleDelta().y()返回滚轮在Y轴上的滚动角度
//    // 正值表示向上滚动（远离用户），负值表示向下滚动（靠近用户）
//    qDebug()<<e->angleDelta().y();
//    
//    // 检查Ctrl键是否被按下
//    if(ctrlKeyPressed == true)
//    {
//        // 向上滚动：放大字体
//        if(e->angleDelta().y()>0)
//        {
//            zoomIn();  // 调用放大函数
//        }
//        // 向下滚动：缩小字体
//        else
//        {
//            zoomOut(); // 调用缩小函数
//        }
//        // 标记事件已被处理，阻止事件继续传播
//        // 这样可以防止同时触发文本编辑器的默认滚动行为
//        e->accept();
//    }
//    else
//    {
//        // 如果Ctrl键未按下，调用父类的默认滚轮处理
//        // 保持正常的文本滚动功能
//        QTextEdit::wheelEvent(e);
//    }
}

/**
 * @brief 键盘按下事件处理函数
 * @param e 键盘事件对象，包含按下的键信息
 * 
 * 主要用于检测Ctrl键的按下状态
 * 当检测到Ctrl键被按下时，更新内部状态标志
 * 这个状态将用于后续的滚轮事件处理判断
 */
void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    // 检查按下的键是否为Ctrl键
    // Qt::Key_Control是Qt定义的Ctrl键枚举值
    if(e->key() == Qt::Key_Control)
    {
        // 调试输出，用于开发时验证Ctrl键检测是否正常
        //qDebug()<<"ctrl Pressed";
        
        // 设置Ctrl键状态标志为true，表示Ctrl键当前被按下
        ctrlKeyPressed = true;
    }
    
    // 调用父类的键盘按下事件处理函数
    // 确保其他按键的正常处理不受影响
    QTextEdit::keyPressEvent(e);
}

/**
 * @brief 键盘释放事件处理函数
 * @param e 键盘事件对象，包含释放的键信息
 * 
 * 主要用于检测Ctrl键的释放状态
 * 当检测到Ctrl键被释放时，及时更新内部状态标志
 * 确保状态跟踪的准确性和及时性
 */
void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    // 检查释放的键是否为Ctrl键
    if(e->key() == Qt::Key_Control)
    {
        // 调试输出，用于开发时验证Ctrl键释放检测是否正常
        //qDebug()<<"ctrl Release";
        
        // 设置Ctrl键状态标志为false，表示Ctrl键已被释放
        ctrlKeyPressed = false;
    }
    
    // 调用父类的键盘释放事件处理函数
    // 确保其他按键的正常处理不受影响
    QTextEdit::keyReleaseEvent(e);
}
