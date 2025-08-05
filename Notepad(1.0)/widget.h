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
    QFile file;//�����Ա����
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void zoomIn();
    void zoomOut();
    //ʵ���¼����˹���
    //QObject *watched���ò���ָ��������ڱ���صĶ���Ҳ�����¼�ԭ��Ҫ���ݵ��Ķ���
    //QEvent *event������һ��ָ���¼������ָ�룬
    //�¼������а������¼��ľ������ͣ�������������̰����ȣ��Լ�������ݡ�
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
