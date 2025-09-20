#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>



class MyTextEdit : public QTextEdit
{
public:
    //�� MyTextEdit ������г�ʼ�������Ұ������õ������ڲ��� parent �С�
    //�� Qt ��Ӧ�ó�������ڲ���֮��ͨ�����ӹ�ϵ������һ���㼶�ṹ��
    //����������ʵ����Դ����ͽ��沼�ֵĹ��ܡ�����ʵ���������ܡ�
    MyTextEdit(QWidget *parent);
protected:
    //�������¼�
    void wheelEvent(QWheelEvent *e) override;
    //Ctrl���������¼�
    void keyPressEvent(QKeyEvent *e) override;
    //Ctrl�����ɿ��¼�
    void keyReleaseEvent(QKeyEvent *e) override;
private:
    //���ڱ��Ctrl����״̬
    bool ctrlKeyPressed = 0;
};

#endif // MYTEXTEDIT_H
