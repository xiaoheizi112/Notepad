#include "mytextedit.h"

#include <QWheelEvent>
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent)
{

}
//�����������¼���ʵ���� Ctrl + ���� �����ı� �Ĺ���
void MyTextEdit::wheelEvent(QWheelEvent *e)
{
//    //��ֵ��ʾ���Ϲ�������ֵ��ʾ���¹���
//    qDebug()<<e->angleDelta().y();
//    //Ctrl���º�
//    if(ctrlKeyPressed == 1)
//    {
//        //���ϷŴ�
//        if(e->angleDelta().y()>0)
//        {
//            zoomIn();
//        }
//        //������С
//        else
//        {
//            zoomOut();
//        }
//        //����¼��Ѵ�����ֹ��������
//        e->accept();
//    }
//    else
//    {
//        //���û���ʵ�֣�����ԭ�й�������
//        QTextEdit::wheelEvent(e);
//    }
}
//������̰��������µ��¼�
void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    //�жϰ��µ��Ƿ�Ϊ Ctrl ��
    if(e->key() == Qt::Key_Control)
    {
        //qDebug()<<"ctrl Pressed";
        ctrlKeyPressed = 1;
    }
    QTextEdit::keyPressEvent(e);
}
//������̰������ɿ����¼�
void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control)
    {
        //qDebug()<<"ctrl Release";
        ctrlKeyPressed = 0;
    }
    QTextEdit::keyPressEvent(e);
}
