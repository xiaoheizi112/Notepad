#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>



class MyTextEdit : public QTextEdit
{
public:
    //对 MyTextEdit 对象进行初始化，并且把它放置到父窗口部件 parent 中。
    //在 Qt 的应用程序里，窗口部件之间通过父子关系构建成一个层级结构，
    //这样有助于实现资源管理和界面布局的功能。可以实现提升功能。
    MyTextEdit(QWidget *parent);
protected:
    //鼠标滚轮事件
    void wheelEvent(QWheelEvent *e) override;
    //Ctrl按键按下事件
    void keyPressEvent(QKeyEvent *e) override;
    //Ctrl按键松开事件
    void keyReleaseEvent(QKeyEvent *e) override;
private:
    //用于标记Ctrl键的状态
    bool ctrlKeyPressed = 0;
};

#endif // MYTEXTEDIT_H
