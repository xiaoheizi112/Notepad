/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mytextedit.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetButtons;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpen;
    QPushButton *btnSave;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnFont;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    MyTextEdit *textEdit;
    QWidget *widgetBotton;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelPosition;
    QLabel *labelCode;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(680, 444);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/jishiben/d0.png"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 680, 444));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetButtons = new QWidget(layoutWidget);
        widgetButtons->setObjectName(QString::fromUtf8("widgetButtons"));
        widgetButtons->setMinimumSize(QSize(0, 60));
        widgetButtons->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        layoutWidget1 = new QWidget(widgetButtons);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 5, 660, 60));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        btnOpen = new QPushButton(layoutWidget1);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setMinimumSize(QSize(40, 40));
        btnOpen->setMaximumSize(QSize(40, 40));
        btnOpen->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/jishiben/c0.png);}\n"
"QPushButton:hover {border-image: url(:/jishiben/c1.png);}\n"
"QPushButton:pressed {border-image: url(:/jishiben/c2.png);}"));

        horizontalLayout->addWidget(btnOpen);

        btnSave = new QPushButton(layoutWidget1);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(40, 40));
        btnSave->setMaximumSize(QSize(40, 40));
        btnSave->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/jishiben/a0.png);}\n"
"QPushButton:hover {border-image: url(:/jishiben/a1.png);}\n"
"QPushButton:pressed {border-image: url(:/jishiben/a2.png);}"));

        horizontalLayout->addWidget(btnSave);

        btnClose = new QPushButton(layoutWidget1);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setMinimumSize(QSize(40, 40));
        btnClose->setMaximumSize(QSize(40, 40));
        btnClose->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/jishiben/b0.png);}\n"
"QPushButton:hover {border-image: url(:/jishiben/b1.png);}\n"
"QPushButton:pressed {border-image: url(:/jishiben/b2.png);}"));

        horizontalLayout->addWidget(btnClose);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnFont = new QPushButton(layoutWidget1);
        btnFont->setObjectName(QString::fromUtf8("btnFont"));
        btnFont->setMinimumSize(QSize(40, 40));
        btnFont->setMaximumSize(QSize(40, 40));
        btnFont->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/jishiben/f0.png);}"));

        horizontalLayout->addWidget(btnFont);

        btnZoomIn = new QPushButton(layoutWidget1);
        btnZoomIn->setObjectName(QString::fromUtf8("btnZoomIn"));
        btnZoomIn->setMinimumSize(QSize(40, 40));
        btnZoomIn->setMaximumSize(QSize(40, 40));
        btnZoomIn->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/jishiben/e0.png);}"));

        horizontalLayout->addWidget(btnZoomIn);

        btnZoomOut = new QPushButton(layoutWidget1);
        btnZoomOut->setObjectName(QString::fromUtf8("btnZoomOut"));
        btnZoomOut->setMinimumSize(QSize(40, 40));
        btnZoomOut->setMaximumSize(QSize(40, 40));
        btnZoomOut->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/jishiben/e1.png);}"));

        horizontalLayout->addWidget(btnZoomOut);


        verticalLayout->addWidget(widgetButtons);

        textEdit = new MyTextEdit(layoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(textEdit);

        widgetBotton = new QWidget(layoutWidget);
        widgetBotton->setObjectName(QString::fromUtf8("widgetBotton"));
        widgetBotton->setMinimumSize(QSize(0, 40));
        widgetBotton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        horizontalLayout_3 = new QHBoxLayout(widgetBotton);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        labelPosition = new QLabel(widgetBotton);
        labelPosition->setObjectName(QString::fromUtf8("labelPosition"));

        horizontalLayout_2->addWidget(labelPosition);

        labelCode = new QLabel(widgetBotton);
        labelCode->setObjectName(QString::fromUtf8("labelCode"));

        horizontalLayout_2->addWidget(labelCode);

        comboBox = new QComboBox(widgetBotton);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(100, 0));
        comboBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(widgetBotton);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "MynoteBook", nullptr));
        btnOpen->setText(QString());
        btnSave->setText(QString());
        btnClose->setText(QString());
        btnFont->setText(QString());
        btnZoomIn->setText(QString());
        btnZoomOut->setText(QString());
        labelPosition->setText(QCoreApplication::translate("Widget", "\347\254\2541\350\241\214\347\254\2541\345\210\227", nullptr));
        labelCode->setText(QCoreApplication::translate("Widget", "UTF-8", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "UTF-8", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "UTF-16", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "GBK", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Widget", "ANSI", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Widget", "GB2312", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
