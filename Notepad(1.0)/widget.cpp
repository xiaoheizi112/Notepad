#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QShortcut>
#include <QWheelEvent>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //��װ�¼�������
    ui->textEdit->installEventFilter(this);
    //����һ��ָ�� QShortcut �����ָ�룬���ڴ��� "��" �����Ŀ�ݼ�
    //this:ָ����ǰ������Ϊ��ݼ��ĸ�����ȷ���봰����������һ��
    QShortcut *shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);
    //����һ��ָ�� QShortcut �����ָ�룬���ڴ��� "����" �����Ŀ�ݼ�
    QShortcut *shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")),this);
    //��ӷŴ�Ŀ�ݼ�
    QShortcut *shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+SHIFT+=", "File|Save")),this);
    //�����С�Ŀ�ݼ�
    QShortcut *shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+SHIFT+-", "File|Save")),this);
    //connect(...):Qt ���źŲ����Ӻ���
    //shortcutOpen:�źŷ����ߣ���֮ǰ������ "��" ��ݼ�����
    //&QShortcut::activated:�ź����ͣ�����ݼ�������ʱ�������ź�
    //[=]():Lambda ���ʽ������������
    //[=]:��ֵ����ʽ��ȡ�ⲿ������ȷ�����Է��ʵ�ǰ����ĳ�Ա
    //on_btnOpen_clicked():Lambda �����壬���� "��" ��ť�ĵ��������
    connect(shortcutOpen,&QShortcut::activated,[=](){
        on_btnOpen_clicked();
    });
    connect(shortcutSave,&QShortcut::activated,[=](){
        on_btnSave_clicked();
    });
    connect(shortcutZoomIn,&QShortcut::activated,[=](){
        zoomIn();
    });
    connect(shortcutZoomOut,&QShortcut::activated,[=](){
        zoomOut();
    });

    this->setLayout(ui->verticalLayout);
    //currentIndexChanged:���û�ѡ�������б��еĲ�ͬ��ʱ�ᴥ������źţ�
    //�����ݵ�ǰѡ������������������ͣ���
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(onCurrentIndexChanged(int)));
    //cursorPositionChanged():
    //QTextEdit �Ĺ��λ�øı�ʱ�Զ��������źţ���Я��������
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),
            this,SLOT(onCursorPositionChanged()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::zoomIn()
{
    //���TextEdit�ĵ�ǰ������Ϣ
    QFont font = ui->textEdit->font();
    //��õ�ǰ����Ĵ�С
    int fontSize = font.pointSize();
    if(fontSize == -1) return;
    //�ı��С�������������С
    int newfontSize = fontSize+1;
    font.setPointSize(newfontSize);
    ui->textEdit->setFont(font);
}

void Widget::zoomOut()
{
    //���TextEdit�ĵ�ǰ������Ϣ
    QFont font = ui->textEdit->font();
    //��õ�ǰ����Ĵ�С
    int fontSize = font.pointSize();
    if(fontSize == -1) return;
    //�ı��С�������������С
    int newfontSize = fontSize-1;
    font.setPointSize(newfontSize);
    ui->textEdit->setFont(font);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    //����⵽�����ֹ���ʱ
    if(event->type() == QEvent::Wheel)
    {
        //ʵʱ�жϵ�ǰ�Ƿ���Ctrl��
        if(QGuiApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            //����ǿת
            //dynamic_cast:ר�����ڴ������Ķ�̬�ԣ�ֻ������ָ������ã����漰������������麯����
            QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);
            if(wheelEvent->angleDelta().y()>0)
            {
                zoomIn();
            }
            else
            {
                zoomOut();
            }
            //���ɹ����� Ctrl + �����¼������� true ��ʾ�¼��ѱ���ȫ�������ټ������ݡ�
            return true;
        }
        //��δ���� Ctrl �������� false ���¼��������ݸ�Ŀ��ؼ���
        return false;
    }
}

// ���ļ�
void Widget::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                    "D:/QT/",
                                                    tr("Text(*.txt)"));

    if(fileName.isEmpty())
        return;

    ui->textEdit->clear(); // ����ı��༭��

    // ���֮ǰ���ļ��Ǵ򿪵ģ��ȹر���
    if(file.isOpen())
        file.close();

    file.setFileName(fileName);

    // �Զ�дģʽ���ļ�
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<"file open error!";
        return;
    }

    this->setWindowTitle(fileName+" - MynoteBook");

    QTextStream in(&file);
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    // һ���Զ�ȡ�����ļ��������л��з���
    QString content = in.readAll();
    // ֱ�����������ı�����
    ui->textEdit->setPlainText(content);
}
void Widget::on_btnSave_clicked()
{
    //�ļ�δ��ʱд�뱣���ļ�
    if(!file.isOpen())
    {
        //���ļ�����Ի���
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "D:/QT/untitled.txt",
                                   tr("Text (*.txt *.doc)"));
        // �û�ȡ��ѡ��ֱ���˳�
        if(fileName.isEmpty()) return;
        //�����ļ����󲢴�
        file.setFileName(fileName);
        // ��ֻдģʽ�򿪣����Զ�����ļ�����
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"file open error";
        }
        this->setWindowTitle(fileName+" - MynoteBook");
    }
    else
    {
        // ����ļ��Ѵ򿪣���Ҫ�����õ��ļ���ͷ���������
        file.resize(0);
        file.seek(0);
    }
    QTextStream out(&file);
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    //��ȡ�ı��༭������������
    QString context = ui->textEdit->toPlainText();
    //������д���ļ�
    out<<context;
}
//�ر��ļ�
void Widget::on_btnClose_clicked()
{
    int ret = QMessageBox::warning(this, tr("MyNoteBook Notice:"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Save | QMessageBox::Discard
                                     | QMessageBox::Cancel,
                                     QMessageBox::Save);
    switch (ret)
    {
        //����ر�
        case QMessageBox::Save:
            // Save was clicked
            on_btnSave_clicked();
            qDebug()<<"QMessageBox::Save";
            break;
        //ֱ�ӹرղ�����
        case QMessageBox::Discard:
            // Don't Save was clicked
            qDebug()<<"QMessageBox::Discard:";
            break;
        //ȡ�����������ر��ļ�
        case QMessageBox::Cancel:
            // Cancel was clicked
            qDebug()<<"QMessageBox::Cancel";
            return;
        default:
            break;
     }
    //����ļ��Ƿ�򿪣��������ر��ļ�������ı��༭�������
    if(file.isOpen())
    {
        file.close();
    }
    ui->textEdit->clear();
    this->setWindowTitle("MynoteBook");
}
//�ļ���ʽ����ʱͨ�����ĸ�ʽ���¶�д��ʽ��ȷ�ļ�
void Widget::onCurrentIndexChanged(int index)
{
    ui->textEdit->clear();
    if(file.isOpen())
    {
        QTextStream in(&file);
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        //seek���ù��ص���ʼλ��
        file.seek(0);
        while(!in.atEnd())
        {
            QString context = in.readLine();
            //qDebug()<<qPrintable(context);
            ui->textEdit->append(context);
        }
    }
}
//�������У����õ�ǰ�и���
void Widget::onCursorPositionChanged()
{
    //ui->textEdit->textCursor():��ȡtextEdit���ı����ĵ�ǰ״̬��
    QTextCursor cursor = ui->textEdit->textCursor();

    //qDebug()<<cursor.columnNumber()+1<<","<<cursor.blockNumber()+1;

    //��ֵ���͵��кź��к�ת��Ϊ�ַ������͡�
    QString blockNum = QString::number(cursor.blockNumber()+1);
    QString columnNum = QString::number(cursor.columnNumber()+1);

    //ƴ���ַ���
    const QString labelMes = "L:"+blockNum+"C:"+columnNum;

    //���±�ǩ�ؼ�����ʾ���ݡ�
    ui->labelPosition->setText(labelMes);
    //���õ�ǰ����
    //������һ����Ϊ extraSelection ���б����ڴ洢��Ҫ������ʾ���ı�����
    //QTextEdit::ExtraSelection ��һ��������ı�ѡ���������ͣ��������Զ����ı�����ʾЧ����
    QList<QTextEdit::ExtraSelection> extraSelection;
    //������һ�� ExtraSelection ���� ext���������õ���������������ԡ�
    QTextEdit::ExtraSelection ext;
    //1.֪����ǰ��
    //��ȡ��ǰ�ı��༭��ui->textEdit���Ĺ��λ�ã������丳ֵ�� ext ����� cursor ���ԡ���һ��ȷ���˸�����ʾ����ʼλ�á�
    ext.cursor = ui->textEdit->textCursor();
    //������һ����ɫ�Ļ�ˢ��QBrush�����������ø�������ı�����ɫ��
    QBrush qBrush(Qt::lightGray);
    //2.��ɫ
    //��֮ǰ�����Ļ�ɫ��ˢӦ�õ� ext ����ĸ�ʽ��format���У����ø�������ı���ɫΪ��ɫ��
    ext.format.setBackground(qBrush);
    //���ø�����������ԣ�ʹ����չ�����еĿ�ȣ���ʹ�ı�û���������С���������ȷ�����ж���������ʾ��
    ext.format.setProperty(QTextFormat::FullWidthSelection,true);
    //����»���
    ext.format.setFontUnderline(true);
    //3.����
    //�����úõ� ext ������ӵ�֮ǰ������ extraSelection �б��С�
    extraSelection.append(ext);
    //�����úõĸ��������б�Ӧ�õ��ı��༭��ui->textEdit���У�ʹ���õĸ���Ч����ʾ�ڽ����ϡ�
    ui->textEdit->setExtraSelections(extraSelection);
}
