/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
// #include <QtWidgets/QApplication>
// #include <QtWidgets/QGridLayout>
// #include <QtWidgets/QHBoxLayout>
// #include <QtWidgets/QLCDNumber>
// #include <QtWidgets/QLabel>
// #include <QtWidgets/QMainWindow>
// #include <QtWidgets/QPushButton>
// #include <QtWidgets/QSpacerItem>
// #include <QtWidgets/QStackedWidget>
// #include <QtWidgets/QVBoxLayout>
// #include <QtWidgets/QWidget>

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *Time_label_1;
    QSpacerItem *verticalSpacer_2;
    QLabel *Tips_label_1;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *Time_label_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *Tips_label_2;
    QLabel *Tips_label_3;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_6;
    QLCDNumber *password_lcd;
    QSpacerItem *verticalSpacer_5;
    QWidget *page_3;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_18;
    QWidget *page_4;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QLabel *jpg_label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMaximumSize(QSize(800, 480));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        Time_label_1 = new QLabel(page);
        Time_label_1->setObjectName(QString::fromUtf8("Time_label_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Time_label_1->sizePolicy().hasHeightForWidth());
        Time_label_1->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(48);
        Time_label_1->setFont(font);
        Time_label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Time_label_1, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        Tips_label_1 = new QLabel(page);
        Tips_label_1->setObjectName(QString::fromUtf8("Tips_label_1"));
        QFont font1;
        font1.setPointSize(40);
        Tips_label_1->setFont(font1);
        Tips_label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Tips_label_1, 2, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        Time_label_2 = new QLabel(page_2);
        Time_label_2->setObjectName(QString::fromUtf8("Time_label_2"));
        QFont font2;
        font2.setPointSize(32);
        Time_label_2->setFont(font2);

        horizontalLayout_2->addWidget(Time_label_2);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Tips_label_2 = new QLabel(page_2);
        Tips_label_2->setObjectName(QString::fromUtf8("Tips_label_2"));
        Tips_label_2->setFont(font2);
        Tips_label_2->setLayoutDirection(Qt::RightToLeft);
        Tips_label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Tips_label_2);

        Tips_label_3 = new QLabel(page_2);
        Tips_label_3->setObjectName(QString::fromUtf8("Tips_label_3"));
        QFont font3;
        font3.setPointSize(20);
        Tips_label_3->setFont(font3);
        Tips_label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_2->addWidget(Tips_label_3);


        horizontalLayout_4->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout_4, 4, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 2, 2, 1, 1);

        password_lcd = new QLCDNumber(page_2);
        password_lcd->setObjectName(QString::fromUtf8("password_lcd"));
        password_lcd->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(password_lcd->sizePolicy().hasHeightForWidth());
        password_lcd->setSizePolicy(sizePolicy1);
        password_lcd->setMinimumSize(QSize(650, 150));
        password_lcd->setMaximumSize(QSize(650, 150));
        password_lcd->setSizeIncrement(QSize(0, 0));
        QFont font4;
        font4.setPointSize(16);
        font4.setBold(false);
        font4.setWeight(50);
        font4.setKerning(true);
        password_lcd->setFont(font4);
        password_lcd->setAcceptDrops(false);
        password_lcd->setLayoutDirection(Qt::LeftToRight);
        password_lcd->setInputMethodHints(Qt::ImhNone);
        password_lcd->setFrameShape(QFrame::WinPanel);
        password_lcd->setFrameShadow(QFrame::Plain);
        password_lcd->setLineWidth(3);
        password_lcd->setMidLineWidth(0);
        password_lcd->setSmallDecimalPoint(true);
        password_lcd->setDigitCount(10);
        password_lcd->setMode(QLCDNumber::Dec);
        password_lcd->setProperty("intValue", QVariant(1234567890));

        gridLayout_2->addWidget(password_lcd, 2, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 6, 1, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_5 = new QGridLayout(page_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        label_3 = new QLabel(page_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font5.setPointSize(18);
        label_3->setFont(font5);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_3, 1, 1, 1, 1);

        label_4 = new QLabel(page_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font5);

        gridLayout_5->addWidget(label_4, 1, 2, 1, 1);

        label_6 = new QLabel(page_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font5);

        gridLayout_5->addWidget(label_6, 2, 2, 1, 1);

        label_5 = new QLabel(page_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font5);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_5, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 4, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_4, 0, 1, 1, 1);

        pushButton_18 = new QPushButton(page_3);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));

        gridLayout_5->addWidget(pushButton_18, 3, 1, 1, 2);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        gridLayout_4 = new QGridLayout(page_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_7, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_8, 0, 4, 1, 1);

        jpg_label = new QLabel(page_4);
        jpg_label->setObjectName(QString::fromUtf8("jpg_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(jpg_label->sizePolicy().hasHeightForWidth());
        jpg_label->setSizePolicy(sizePolicy2);
        jpg_label->setMinimumSize(QSize(614, 460));
        jpg_label->setMaximumSize(QSize(614, 460));
        jpg_label->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(jpg_label, 0, 3, 1, 1);

        stackedWidget->addWidget(page_4);

        gridLayout_3->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Time_label_1->setText(QApplication::translate("MainWindow", "xxxx", nullptr));
        Tips_label_1->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        Time_label_2->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        Tips_label_2->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        Tips_label_3->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "ID\357\274\232", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "xxxx", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "xxxx", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\347\273\221\345\256\232\345\257\206\347\240\201\357\274\232", nullptr));
        pushButton_18->setText(QApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        jpg_label->setText(QApplication::translate("MainWindow", "JPG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
