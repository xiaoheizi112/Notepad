#include "mytextedit.h"

#include <QWheelEvent>
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent)
{

}
//处理鼠标滚轮事件，实现了 Ctrl + 滚轮 缩放文本 的功能
void MyTextEdit::wheelEvent(QWheelEvent *e)
{
//    //正值表示向上滚动，负值表示向下滚动
//    qDebug()<<e->angleDelta().y();
//    //Ctrl按下后
//    if(ctrlKeyPressed == 1)
//    {
//        //向上放大
//        if(e->angleDelta().y()>0)
//        {
//            zoomIn();
//        }
//        //向下缩小
//        else
//        {
//            zoomOut();
//        }
//        //标记事件已处理，阻止继续传播
//        e->accept();
//    }
//    else
//    {
//        //调用基类实现，保持原有滚动功能
//        QTextEdit::wheelEvent(e);
//    }
}
//捕获键盘按键被按下的事件
void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    //判断按下的是否为 Ctrl 键
    if(e->key() == Qt::Key_Control)
    {
        //qDebug()<<"ctrl Pressed";
        ctrlKeyPressed = 1;
    }
    QTextEdit::keyPressEvent(e);
}
//捕获键盘按键被松开的事件
void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control)
    {
        //qDebug()<<"ctrl Release";
        ctrlKeyPressed = 0;
    }
    QTextEdit::keyPressEvent(e);
}
