#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFontDialog>
#include <QList>
#include <QMessageBox>
#include <QShortcut>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QTextStream>

// Widget类的构造函数，负责初始化界面和设置各种功能
// parent: 父窗口指针，用于建立Qt对象层次结构
Widget::Widget(QWidget *parent)
    : QWidget(parent)  // 调用父类QWidget的构造函数
    , ui(new Ui::Widget)  // 创建UI界面对象
{
    // 初始化用户界面，加载.ui文件中定义的控件布局
    ui->setupUi(this);
    
    // 设置文本编辑器自动换行功能
    // setLineWrapMode(): 设置文本换行模式
    // QTextEdit::WidgetWidth: 根据控件宽度自动换行，当文本超出控件宽度时自动换到下一行
    // 这样可以确保所有文本内容都能在窗口内可见，无需水平滚动
    ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    
    // 为文本编辑器安装事件过滤器，用于捕获鼠标滚轮事件实现缩放功能
    ui->textEdit->installEventFilter(this);
    // 创建快捷键对象，实现键盘快速操作功能
    // QKeySequence: Qt的按键序列类，用于定义组合键
    // tr(): 国际化翻译函数，支持多语言界面
    // this: 将当前窗口设为快捷键的父对象，确保生命周期管理正确
    
    // Ctrl+O: 打开文件快捷键
    QShortcut *shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);
    
    // Ctrl+S: 保存文件快捷键
    QShortcut *shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")),this);
    
    // Ctrl+Shift+=: 放大字体快捷键
    QShortcut *shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+SHIFT+=", "File|Save")),this);
    
    // Ctrl+Shift+-: 缩小字体快捷键
    QShortcut *shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+SHIFT+-", "File|Save")),this);
    // 使用Qt信号槽机制连接快捷键与对应的处理函数
    // connect(): Qt核心函数，用于建立信号与槽的连接
    // 参数说明：
    // 1. 信号发送者对象
    // 2. 信号类型（使用函数指针语法 &Class::signal）
    // 3. 槽函数或Lambda表达式
    // [=]: Lambda捕获列表，按值捕获所有外部变量，确保可访问当前对象成员
    
    // 连接打开文件快捷键：当Ctrl+O被按下时，调用打开文件功能
    connect(shortcutOpen,&QShortcut::activated,[=](){
        on_btnOpen_clicked();  // 调用打开按钮的点击处理函数
    });
    
    // 连接保存文件快捷键：当Ctrl+S被按下时，调用保存文件功能
    connect(shortcutSave,&QShortcut::activated,[=](){
        on_btnSave_clicked();  // 调用保存按钮的点击处理函数
    });
    
    // 连接放大字体快捷键：当Ctrl+Shift+=被按下时，调用放大功能
    connect(shortcutZoomIn,&QShortcut::activated,[=](){
        zoomIn();  // 调用字体放大函数
    });
    
    // 连接缩小字体快捷键：当Ctrl+Shift+-被按下时，调用缩小功能
    connect(shortcutZoomOut,&QShortcut::activated,[=](){
        zoomOut();  // 调用字体缩小函数
    });

    // 设置窗口的主布局为垂直布局，确保控件按垂直方向排列
    this->setLayout(ui->verticalLayout);
    
    // 连接编码选择下拉框的信号槽
    // currentIndexChanged(int): 当用户选择不同编码格式时触发
    // 参数int为当前选中项的索引值，用于确定选择的编码类型
    // 使用传统的SIGNAL/SLOT宏语法进行连接
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(onCurrentIndexChanged(int)));
    
    // 连接文本编辑器的光标位置变化信号槽
    // cursorPositionChanged(): 当文本编辑器中光标位置发生变化时自动触发
    // 用于实时更新状态栏中显示的行号和列号信息
    // 同时触发当前行的高亮显示功能
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),
            this,SLOT(onCursorPositionChanged()));
}

// Widget类的析构函数，负责清理资源
// 在对象生命周期结束时自动调用
Widget::~Widget()
{
    // 删除UI对象，释放界面相关的内存资源
    // Qt的父子对象机制会自动处理其他控件的清理
    delete ui;
}

// 字体放大功能实现
// 通过增加字体大小来实现文本放大效果
void Widget::zoomIn()
{
    // 获取文本编辑器当前使用的字体对象
    QFont font = ui->textEdit->font();
    
    // 获取当前字体的点大小（以点为单位的字体大小）
    int fontSize = font.pointSize();
    
    // 检查字体大小是否有效，-1表示无效的字体大小
    if(fontSize == -1) return;
    
    // 将字体大小增加1个点，实现放大效果
    int newfontSize = fontSize+1;
    font.setPointSize(newfontSize);
    
    // 将修改后的字体应用到文本编辑器
    ui->textEdit->setFont(font);
}

// 字体缩小功能实现
// 通过减少字体大小来实现文本缩小效果
void Widget::zoomOut()
{
    // 获取文本编辑器当前使用的字体对象
    QFont font = ui->textEdit->font();
    
    // 获取当前字体的点大小
    int fontSize = font.pointSize();
    
    // 检查字体大小是否有效，-1表示无效的字体大小
    if(fontSize == -1) return;
    
    // 将字体大小减少1个点，实现缩小效果
    // 注意：应该添加最小字体大小限制以防止字体过小
    int newfontSize = fontSize-1;
    font.setPointSize(newfontSize);
    
    // 将修改后的字体应用到文本编辑器
    ui->textEdit->setFont(font);
}

/**
 * @brief 字体设置功能实现
 * 
 * 打开Qt标准字体选择对话框，允许用户自定义字体设置：
 * - 字体族：选择不同的字体类型（如宋体、微软雅黑、Consolas等）
 * - 字体大小：设置字体的点大小
 * - 字体样式：设置粗体、斜体、下划线等样式
 * - 实时预览：在对话框中可以预览字体效果
 * 
 * 用户确认选择后，新字体会立即应用到文本编辑器
 */
void Widget::setFont()
{
    // 获取文本编辑器当前使用的字体
    // 作为字体对话框的初始字体设置
    QFont currentFont = ui->textEdit->font();
    
    // 创建并显示字体选择对话框
    // QFontDialog::getFont(): Qt提供的标准字体选择对话框
    // 参数说明：
    // - &ok: 用于接收用户是否点击了确定按钮的布尔值
    // - currentFont: 对话框打开时显示的初始字体
    // - this: 对话框的父窗口
    // - tr("选择字体"): 对话框的标题文本，支持国际化
    bool ok;
    QFont selectedFont = QFontDialog::getFont(&ok, currentFont, this, tr("选择字体"));
    
    // 检查用户是否点击了确定按钮
    // 如果用户点击取消或关闭对话框，ok为false，不执行字体更改
    if (ok) {
        // 用户确认选择，将新字体应用到文本编辑器
        // setFont(): QTextEdit的方法，用于设置控件的字体
        ui->textEdit->setFont(selectedFont);
        
        // 可选：输出调试信息，显示选择的字体信息
        qDebug() << "字体已更改为:" << selectedFont.family() 
                 << "大小:" << selectedFont.pointSize()
                 << "粗体:" << selectedFont.bold()
                 << "斜体:" << selectedFont.italic();
    }
}

// 事件过滤器函数：拦截并处理特定的事件
// 主要用于实现Ctrl+鼠标滚轮的字体缩放功能
// watched: 被监视的对象（这里是textEdit）
// event: 发生的事件对象
// 返回值: true表示事件已处理，false表示继续传递事件
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    // 检查是否为鼠标滚轮事件
    // QEvent::Wheel 是Qt定义的滚轮事件类型枚举值
    if(event->type() == QEvent::Wheel)
    {
        // 检查当前是否按下了Ctrl键
        // QGuiApplication::keyboardModifiers() 获取当前按下的修饰键状态
        // Qt::ControlModifier 表示Ctrl键的修饰符
        if(QGuiApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            // 将通用事件指针安全转换为滚轮事件指针
            // dynamic_cast 进行运行时类型检查，确保转换安全
            // 如果转换失败会返回nullptr
            QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);
            
            // 检查滚轮滚动方向
            // angleDelta().y() > 0 表示向上滚动（远离用户）
            // angleDelta().y() < 0 表示向下滚动（靠近用户）
            if(wheelEvent->angleDelta().y()>0)
            {
                zoomIn();  // 向上滚动：放大字体
            }
            else
            {
                zoomOut(); // 向下滚动：缩小字体
            }
            
            // 返回true表示事件已被完全处理，阻止事件继续传递
            // 这样可以防止滚轮事件同时触发文本编辑器的默认滚动行为
            return true;
        }
    }
    
    // 对于其他类型的事件或未按下Ctrl键的滚轮事件
    // 调用父类的事件过滤器进行默认处理，保持正常的事件传递机制
    return QWidget::eventFilter(watched, event);
}

// 打开文件按钮的点击事件处理函数
// 实现文件选择、打开、读取和显示功能
void Widget::on_btnOpen_clicked()
{
    // 使用QFileDialog显示文件选择对话框
    // 参数说明：
    // this: 父窗口
    // tr("Open File"): 对话框标题（支持国际化）
    // "D:/QT/": 默认打开路径
    // tr("Text(*.txt)"): 文件过滤器，只显示txt文件
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                    "D:/QT/",
                                                    tr("Text(*.txt)"));

    // 检查用户是否取消了文件选择
    // isEmpty()返回true表示用户点击了取消按钮
    if(fileName.isEmpty())
        return;

    // 清空文本编辑器中的现有内容，为新文件内容做准备
    ui->textEdit->clear();

    // 检查是否有文件已经打开，如果有则先关闭
    // 这样可以确保文件句柄的正确管理，避免资源泄露
    if(file.isOpen())
        file.close();

    // 设置QFile对象要操作的文件路径
    file.setFileName(fileName);

    // 尝试以读写模式打开文件
    // QIODevice::ReadWrite: 允许读写操作
    // QIODevice::Text: 文本模式，自动处理换行符转换
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<"file open error!";  // 输出错误信息到调试控制台
        return;  // 打开失败则退出函数
    }

    // 更新窗口标题，显示当前打开的文件名
    this->setWindowTitle(fileName+" - MynoteBook");

    // 创建文本流对象，用于从文件中读取文本数据
    // QTextStream提供了便捷的文本读写接口，自动处理编码转换
    QTextStream in(&file);
    
    // 设置文本流的字符编码格式
    // 从下拉框获取用户选择的编码格式（如UTF-8、GBK等）
    // toStdString().c_str()将QString转换为C风格字符串
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    
    // 一次性读取整个文件的所有内容
    // readAll()会读取从当前位置到文件末尾的所有文本
    // 包括换行符、制表符等所有字符
    QString content = in.readAll();
    
    // 将读取的文件内容显示在文本编辑器中
    // setPlainText()会替换编辑器中的所有现有内容
    ui->textEdit->setPlainText(content);
}
// 保存文件按钮的点击事件处理函数
// 实现文件保存功能，支持新建文件和覆盖现有文件
void Widget::on_btnSave_clicked()
{
    // 检查当前是否有文件已打开
    // 如果没有打开文件，需要先让用户选择保存位置
    if(!file.isOpen())
    {
        // 显示文件保存对话框让用户选择保存位置和文件名
        // 参数说明：
        // this: 父窗口
        // tr("Save File"): 对话框标题
        // "D:/QT/untitled.txt": 默认文件名和路径
        // tr("Text (*.txt *.doc)"): 文件类型过滤器
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "D:/QT/untitled.txt",
                                   tr("Text (*.txt *.doc)"));
        
        // 检查用户是否取消了保存操作
        if(fileName.isEmpty()) return;
        
        // 设置QFile对象的文件路径
        file.setFileName(fileName);
        
        // 以只写模式打开文件，如果文件不存在会自动创建
        // QIODevice::WriteOnly: 只写模式
        // QIODevice::Text: 文本模式，处理换行符转换
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"file open error";  // 输出错误信息
            return;  // 打开失败则退出
        }
        
        // 更新窗口标题显示当前文件名
        this->setWindowTitle(fileName+" - MynoteBook");
    }
    else
    {
        // 如果文件已经打开，准备覆盖写入
        // resize(0): 将文件大小调整为0，清空文件内容
        file.resize(0);
        // seek(0): 将文件指针移动到文件开头
        file.seek(0);
    }
    
    // 创建文本流对象用于写入文件
    QTextStream out(&file);
    
    // 设置输出流的字符编码，与用户选择的编码保持一致
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    
    // 从文本编辑器获取所有文本内容
    // toPlainText()返回纯文本，不包含格式信息
    QString context = ui->textEdit->toPlainText();
    
    // 使用流操作符将文本内容写入文件
    // QTextStream会自动处理编码转换和换行符
    out<<context;
}
// 关闭文件
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
        // 保存并关闭
        case QMessageBox::Save:
            // Save was clicked
            on_btnSave_clicked();
            qDebug()<<"QMessageBox::Save";
            break;
        // 直接关闭不保存
        case QMessageBox::Discard:
            // Don't Save was clicked
            qDebug()<<"QMessageBox::Discard:";
            break;
        // 取消操作，不关闭文件
        case QMessageBox::Cancel:
            // Cancel was clicked
            qDebug()<<"QMessageBox::Cancel";
            return;
        default:
            break;
     }
    // 检查文件是否打开，如果是则关闭文件并清空文本编辑器内容
    if(file.isOpen())
    {
        file.close();
    }
    ui->textEdit->clear();
    this->setWindowTitle("MynoteBook");
}

/**
 * @brief 字体设置按钮点击槽函数实现
 * 
 * 响应UI界面中字体设置按钮的点击事件
 * 直接调用setFont()函数打开字体选择对话框
 * 实现用户友好的字体设置功能
 */
void Widget::on_btnFont_clicked()
{
    // 调用字体设置函数
    // setFont()函数会打开Qt标准字体对话框
    // 允许用户选择字体类型、大小、样式等
    // 并将选择的字体应用到文本编辑器
    setFont();
}

/**
 * @brief 字体放大按钮点击槽函数实现
 * 
 * 响应UI界面中字体放大按钮的点击事件
 * 直接调用zoomIn()函数增大文本编辑器字体
 */
void Widget::on_btnZoomIn_clicked()
{
    // 调用字体放大函数
    // zoomIn()函数会将当前字体大小增加1个点
    zoomIn();
}

/**
 * @brief 字体缩小按钮点击槽函数实现
 * 
 * 响应UI界面中字体缩小按钮的点击事件
 * 直接调用zoomOut()函数减小文本编辑器字体
 */
void Widget::on_btnZoomOut_clicked()
{
    // 调用字体缩小函数
    // zoomOut()函数会将当前字体大小减少1个点
    zoomOut();
}

//�ļ���ʽ����ʱͨ �����ĸ�ʽ���¶�д��ʽ��ȷ�ļ�
void Widget::onCurrentIndexChanged(int index)
{
    ui->textEdit->clear();
    if(file.isOpen())
    {
        QTextStream in(&file);
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        // seek设置光标到开始位置
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
    // ui->textEdit->textCursor():获取textEdit中文本光标的当前状态。
    QTextCursor cursor = ui->textEdit->textCursor();

    //qDebug()<<cursor.columnNumber()+1<<","<<cursor.blockNumber()+1;

    // 整数类型的行号和列号转换为字符串类型。
    QString blockNum = QString::number(cursor.blockNumber()+1);
    QString columnNum = QString::number(cursor.columnNumber()+1);

    // 拼接字符串
    const QString labelMes = "L:"+blockNum+"C:"+columnNum;

    // 更新标签控件的显示内容。
    ui->labelPosition->setText(labelMes);
    // 设置当前行高亮
    // 创建一个名为 extraSelection 的列表，用于存储需要额外显示的文本选区
    // QTextEdit::ExtraSelection 是一个描述文本选区及其样式的类型，可以用来自定义文本的显示效果。
    QList<QTextEdit::ExtraSelection> extraSelection;
    // 创建一个 ExtraSelection 对象 ext，用来设置高亮行的各种属性。
    QTextEdit::ExtraSelection ext;
    // 1.指定当前行
    // 获取当前文本编辑器ui->textEdit中的光标位置，并将其赋值给 ext 对象的 cursor 属性。这一步确定了高亮显示的起始位置。
    ext.cursor = ui->textEdit->textCursor();
    // 创建一个浅灰色的画刷（QBrush），用来设置高亮行的文本背景色。
    QBrush qBrush(Qt::lightGray);
    // 2.着色
    // 将之前创建的灰色画刷应用到 ext 对象的格式（format）中，设置高亮行的文本背景色为灰色。
    ext.format.setBackground(qBrush);
    // 设置高亮行的特殊属性，使其扩展到整行的宽度，即使文本没有填满整行。这确保了整行都会被高亮显示。
    ext.format.setProperty(QTextFormat::FullWidthSelection,true);
    // 设置下划线
    ext.format.setFontUnderline(true);
    // 3.应用
    // 将设置好的 ext 对象添加到之前创建的 extraSelection 列表中。
    extraSelection.append(ext);
    // 将设置好的高亮样式列表应用到文本编辑器ui->textEdit中，使设置的高亮效果显示在界面上。
    ui->textEdit->setExtraSelections(extraSelection);
}
