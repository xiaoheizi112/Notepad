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
    //安装事件过滤器
    ui->textEdit->installEventFilter(this);
    //创建一个指向 QShortcut 对象的指针，用于处理 "打开" 操作的快捷键
    //this:指定当前对象作为快捷键的父对象，确保与窗口生命周期一致
    QShortcut *shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);
    //创建一个指向 QShortcut 对象的指针，用于处理 "保存" 操作的快捷键
    QShortcut *shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")),this);
    //添加放大的快捷键
    QShortcut *shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+SHIFT+=", "File|Save")),this);
    //添加缩小的快捷键
    QShortcut *shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+SHIFT+-", "File|Save")),this);
    //connect(...):Qt 的信号槽连接函数
    //shortcutOpen:信号发送者，即之前创建的 "打开" 快捷键对象
    //&QShortcut::activated:信号类型，当快捷键被触发时发出此信号
    //[=]():Lambda 表达式（匿名函数）
    //[=]:以值捕获方式获取外部变量，确保可以访问当前对象的成员
    //on_btnOpen_clicked():Lambda 函数体，调用 "打开" 按钮的点击处理函数
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
    //currentIndexChanged:当用户选择下拉列表中的不同项时会触发这个信号，
    //并传递当前选中项的索引（整数类型）。
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(onCurrentIndexChanged(int)));
    //cursorPositionChanged():
    //QTextEdit 的光标位置改变时自动发出此信号，不携带参数。
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),
            this,SLOT(onCursorPositionChanged()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::zoomIn()
{
    //获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //获得当前字体的大小
    int fontSize = font.pointSize();
    if(fontSize == -1) return;
    //改变大小，并设置字体大小
    int newfontSize = fontSize+1;
    font.setPointSize(newfontSize);
    ui->textEdit->setFont(font);
}

void Widget::zoomOut()
{
    //获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //获得当前字体的大小
    int fontSize = font.pointSize();
    if(fontSize == -1) return;
    //改变大小，并设置字体大小
    int newfontSize = fontSize-1;
    font.setPointSize(newfontSize);
    ui->textEdit->setFont(font);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    //当检测到鼠标滚轮滚动时
    if(event->type() == QEvent::Wheel)
    {
        //实时判断当前是否按下Ctrl键
        if(QGuiApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            //类型强转
            //dynamic_cast:专门用于处理对象的多态性，只能用于指针和引用，且涉及对象类必须有虚函数。
            QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);
            if(wheelEvent->angleDelta().y()>0)
            {
                zoomIn();
            }
            else
            {
                zoomOut();
            }
            //若成功处理 Ctrl + 滚轮事件，返回 true 表示事件已被完全处理，不再继续传递。
            return true;
        }
        //若未按下 Ctrl 键，返回 false 让事件继续传递给目标控件。
        return false;
    }
}

// 打开文件
void Widget::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                    "D:/QT/",
                                                    tr("Text(*.txt)"));

    if(fileName.isEmpty())
        return;

    ui->textEdit->clear(); // 清空文本编辑框

    // 如果之前的文件是打开的，先关闭它
    if(file.isOpen())
        file.close();

    file.setFileName(fileName);

    // 以读写模式打开文件
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<"file open error!";
        return;
    }

    this->setWindowTitle(fileName+" - MynoteBook");

    QTextStream in(&file);
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    // 一次性读取整个文件（含所有换行符）
    QString content = in.readAll();
    // 直接设置完整文本内容
    ui->textEdit->setPlainText(content);
}
void Widget::on_btnSave_clicked()
{
    //文件未打开时写入保存文件
    if(!file.isOpen())
    {
        //打开文件保存对话框
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "D:/QT/untitled.txt",
                                   tr("Text (*.txt *.doc)"));
        // 用户取消选择，直接退出
        if(fileName.isEmpty()) return;
        //创建文件对象并打开
        file.setFileName(fileName);
        // 以只写模式打开，会自动清空文件内容
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"file open error";
        }
        this->setWindowTitle(fileName+" - MynoteBook");
    }
    else
    {
        // 如果文件已打开，需要先重置到文件开头并清空内容
        file.resize(0);
        file.seek(0);
    }
    QTextStream out(&file);
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    //获取文本编辑框中所有内容
    QString context = ui->textEdit->toPlainText();
    //将内容写入文件
    out<<context;
}
//关闭文件
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
        //保存关闭
        case QMessageBox::Save:
            // Save was clicked
            on_btnSave_clicked();
            qDebug()<<"QMessageBox::Save";
            break;
        //直接关闭不保存
        case QMessageBox::Discard:
            // Don't Save was clicked
            qDebug()<<"QMessageBox::Discard:";
            break;
        //取消操作，不关闭文件
        case QMessageBox::Cancel:
            // Cancel was clicked
            qDebug()<<"QMessageBox::Cancel";
            return;
        default:
            break;
     }
    //检查文件是否打开，如果打开则关闭文件并清空文本编辑框的内容
    if(file.isOpen())
    {
        file.close();
    }
    ui->textEdit->clear();
    this->setWindowTitle("MynoteBook");
}
//文件格式错误时通过更改格式重新读写格式正确文件
void Widget::onCurrentIndexChanged(int index)
{
    ui->textEdit->clear();
    if(file.isOpen())
    {
        QTextStream in(&file);
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        //seek：让光标回到初始位置
        file.seek(0);
        while(!in.atEnd())
        {
            QString context = in.readLine();
            //qDebug()<<qPrintable(context);
            ui->textEdit->append(context);
        }
    }
}
//设置行列，设置当前行高亮
void Widget::onCursorPositionChanged()
{
    //ui->textEdit->textCursor():获取textEdit中文本光标的当前状态。
    QTextCursor cursor = ui->textEdit->textCursor();

    //qDebug()<<cursor.columnNumber()+1<<","<<cursor.blockNumber()+1;

    //数值类型的行号和列号转换为字符串类型。
    QString blockNum = QString::number(cursor.blockNumber()+1);
    QString columnNum = QString::number(cursor.columnNumber()+1);

    //拼接字符串
    const QString labelMes = "L:"+blockNum+"C:"+columnNum;

    //更新标签控件的显示内容。
    ui->labelPosition->setText(labelMes);
    //设置当前高亮
    //创建了一个名为 extraSelection 的列表，用于存储需要高亮显示的文本区域。
    //QTextEdit::ExtraSelection 是一种特殊的文本选择区域类型，可用于自定义文本的显示效果。
    QList<QTextEdit::ExtraSelection> extraSelection;
    //创建了一个 ExtraSelection 对象 ext，用于设置单个高亮区域的属性。
    QTextEdit::ExtraSelection ext;
    //1.知道当前行
    //获取当前文本编辑框（ui->textEdit）的光标位置，并将其赋值给 ext 对象的 cursor 属性。这一步确定了高亮显示的起始位置。
    ext.cursor = ui->textEdit->textCursor();
    //创建了一个灰色的画刷（QBrush），用于设置高亮区域的背景颜色。
    QBrush qBrush(Qt::lightGray);
    //2.颜色
    //将之前创建的灰色画刷应用到 ext 对象的格式（format）中，设置高亮区域的背景色为灰色。
    ext.format.setBackground(qBrush);
    //设置高亮区域的属性，使其扩展到整行的宽度，即使文本没有填满整行。这样可以确保整行都被高亮显示。
    ext.format.setProperty(QTextFormat::FullWidthSelection,true);
    //添加下划线
    ext.format.setFontUnderline(true);
    //3.设置
    //将配置好的 ext 对象添加到之前创建的 extraSelection 列表中。
    extraSelection.append(ext);
    //将配置好的高亮区域列表应用到文本编辑框（ui->textEdit）中，使设置的高亮效果显示在界面上。
    ui->textEdit->setExtraSelections(extraSelection);
}
