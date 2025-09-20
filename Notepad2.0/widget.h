#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @brief Widget类 - 主窗口类
 * 
 * 这是记事本应用程序的主窗口类，继承自QWidget
 * 提供了完整的文本编辑功能，包括：
 * 
 * 核心功能：
 * - 文件操作：打开、保存、关闭文件
 * - 文本编辑：支持多种字符编码格式
 * - 字体缩放：通过快捷键或Ctrl+滚轮进行缩放
 * - 光标跟踪：实时显示当前行号和列号
 * - 当前行高亮：自动高亮显示光标所在行
 * 
 * 技术特性：
 * - 使用Qt的信号槽机制进行事件处理
 * - 实现了事件过滤器来处理特殊交互
 * - 支持多种文本编码格式的读写
 * - 提供了现代化的用户界面体验
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 文件操作对象
     * 
     * QFile类的实例，用于处理所有文件相关操作：
     * - 文件的打开和关闭
     * - 文件内容的读取和写入
     * - 文件状态的管理和检查
     * 
     * 作为公共成员，便于在各个成员函数中访问
     */
    QFile file;
    
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，默认为nullptr
     * 
     * 初始化主窗口，设置UI界面，创建快捷键，
     * 连接信号槽，安装事件过滤器等
     */
    Widget(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     * 
     * 清理UI资源，Qt的父子对象机制会自动
     * 处理其他控件和对象的清理工作
     */
    ~Widget();
    
    /**
     * @brief 字体放大功能
     * 
     * 将文本编辑器的字体大小增加1个点
     * 可通过快捷键Ctrl+Shift+=或Ctrl+滚轮向上调用
     */
    void zoomIn();
    
    /**
     * @brief 字体缩小功能
     * 
     * 将文本编辑器的字体大小减少1个点
     * 可通过快捷键Ctrl+Shift+-或Ctrl+滚轮向下调用
     */
    void zoomOut();
    
    /**
     * @brief 字体设置功能
     * 
     * 打开字体选择对话框，允许用户选择：
     * - 字体类型（如宋体、微软雅黑等）
     * - 字体大小（以点为单位）
     * - 字体样式（粗体、斜体、下划线等）
     * 选择完成后将新字体应用到文本编辑器
     */
    void setFont();
    
    /**
     * @brief 事件过滤器函数
     * @param watched 被监视的对象指针
     * @param event 事件对象指针
     * @return true表示事件已处理，false表示继续传递事件
     * 
     * 重写QWidget的事件过滤器，主要用于：
     * - 拦截文本编辑器的鼠标滚轮事件
     * - 实现Ctrl+滚轮的字体缩放功能
     * - 阻止缩放时的默认滚动行为
     * 
     * 事件过滤机制说明：
     * - watched: 指向被监视的对象（这里是textEdit）
     * - event: 包含事件的具体类型和相关数据
     * - 返回true会阻止事件继续传递，false则继续传递
     */
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    /**
     * @brief 打开文件按钮点击槽函数
     * 
     * 响应打开按钮点击事件，执行以下操作：
     * - 显示文件选择对话框
     * - 打开用户选择的文件
     * - 读取文件内容并显示在文本编辑器中
     * - 根据选择的编码格式正确解析文件
     * - 更新窗口标题显示文件名
     */
    void on_btnOpen_clicked();

    /**
     * @brief 保存文件按钮点击槽函数
     * 
     * 响应保存按钮点击事件，执行以下操作：
     * - 如果是新文件，显示保存对话框让用户选择位置
     * - 如果是已有文件，直接覆盖保存
     * - 将文本编辑器内容写入文件
     * - 使用用户选择的编码格式进行保存
     * - 更新窗口标题（如果是新文件）
     */
    void on_btnSave_clicked();

    /**
     * @brief 关闭文件按钮点击槽函数
     * 
     * 响应关闭按钮点击事件，执行以下操作：
     * - 检查文件是否有未保存的修改
     * - 如果有修改，弹出确认对话框
     * - 根据用户选择进行保存、丢弃或取消操作
     * - 关闭文件句柄，清空文本编辑器
     * - 重置窗口标题
     */
    void on_btnClose_clicked();

    /**
     * @brief 字体设置按钮点击槽函数
     * 
     * 响应字体设置按钮点击事件，执行以下操作：
     * - 调用setFont()函数打开字体选择对话框
     * - 允许用户选择字体类型、大小和样式
     * - 将选择的字体应用到文本编辑器
     */
    void on_btnFont_clicked();

    /**
     * @brief 字体放大按钮点击槽函数
     * 
     * 响应字体放大按钮点击事件，执行以下操作：
     * - 调用zoomIn()函数增大文本编辑器字体
     * - 将当前字体大小增加1个点
     */
    void on_btnZoomIn_clicked();

    /**
     * @brief 字体缩小按钮点击槽函数
     * 
     * 响应字体缩小按钮点击事件，执行以下操作：
     * - 调用zoomOut()函数减小文本编辑器字体
     * - 将当前字体大小减少1个点
     */
    void on_btnZoomOut_clicked();

    /**
     * @brief 编码格式下拉框选择变化槽函数
     * @param index 当前选中项的索引
     * 
     * 响应编码格式下拉框的选择变化：
     * - 如果当前有文件打开，使用新编码重新读取文件
     * - 将文件指针重置到开头
     * - 用新的编码格式重新解析文件内容
     * - 更新文本编辑器显示
     */
    void onCurrentIndexChanged(int index);

    /**
     * @brief 光标位置变化槽函数
     * 
     * 响应文本编辑器光标位置变化事件：
     * - 获取当前光标的行号和列号
     * - 更新状态标签显示当前位置信息
     * - 设置当前行的高亮显示效果
     * - 创建灰色背景和下划线样式
     * - 应用高亮效果到文本编辑器
     */
    void onCursorPositionChanged();

private:
    /**
     * @brief UI界面对象指针
     * 
     * 指向由Qt Designer生成的UI类实例
     * 通过这个指针可以访问界面上的所有控件：
     * - textEdit: 主要的文本编辑器
     * - comboBox: 编码格式选择下拉框
     * - 各种按钮: 打开、保存、关闭等
     * - 布局管理器: verticalLayout等
     * 
     * UI对象在构造函数中创建，在析构函数中销毁
     */
    Ui::Widget *ui;
};
#endif // WIDGET_H
