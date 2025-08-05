#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QFile file;//定义成员数据
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void zoomIn();
    void zoomOut();
    //实现事件过滤功能
    //QObject *watched：该参数指向的是正在被监控的对象，也就是事件原本要传递到的对象。
    //QEvent *event：这是一个指向事件对象的指针，
    //事件对象中包含了事件的具体类型（像鼠标点击、键盘按键等）以及相关数据。
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_btnOpen_clicked();

    void on_btnSave_clicked();

    void on_btnClose_clicked();

    void onCurrentIndexChanged(int index);

    void onCursorPositionChanged();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
