/********************************************************************************
** Form generated from reading UI file 'PackageManage.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKAGEMANAGE_H
#define UI_PACKAGEMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PackageManageClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_4;
    QProgressBar *progressBar;
    QLabel *label;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *version;
    QLineEdit *lineEdit;
    QPushButton *pushButton_24;
    QPushButton *pushButton_26;
    QPushButton *pushButton_25;
    QPushButton *pushButton_18;
    QPushButton *pushButton;
    QPushButton *pushButton_15;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QTableWidget *tableWidget;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;

    void setupUi(QMainWindow *PackageManageClass)
    {
        if (PackageManageClass->objectName().isEmpty())
            PackageManageClass->setObjectName(QStringLiteral("PackageManageClass"));
        PackageManageClass->resize(1024, 768);
        PackageManageClass->setMinimumSize(QSize(1024, 768));
        PackageManageClass->setMaximumSize(QSize(1024, 768));
        centralWidget = new QWidget(PackageManageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 720, 940, 21));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(true);
        lineEdit_2->setMinimumSize(QSize(500, 20));
        lineEdit_2->setMaximumSize(QSize(500, 20));

        horizontalLayout_7->addWidget(lineEdit_2);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(30, 20));
        pushButton_4->setMaximumSize(QSize(30, 20));

        horizontalLayout_7->addWidget(pushButton_4);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setMinimumSize(QSize(140, 20));
        progressBar->setMaximumSize(QSize(140, 20));
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar->setTextVisible(true);

        horizontalLayout_7->addWidget(progressBar);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(250, 20));
        label->setMaximumSize(QSize(250, 20));

        horizontalLayout_7->addWidget(label);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(12, 13, 942, 32));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        version = new QLabel(layoutWidget1);
        version->setObjectName(QStringLiteral("version"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(version->sizePolicy().hasHeightForWidth());
        version->setSizePolicy(sizePolicy1);
        version->setMinimumSize(QSize(40, 20));
        version->setMaximumSize(QSize(40, 20));

        horizontalLayout_5->addWidget(version);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(80, 20));
        lineEdit->setMaximumSize(QSize(80, 20));

        horizontalLayout_5->addWidget(lineEdit);

        pushButton_24 = new QPushButton(layoutWidget1);
        pushButton_24->setObjectName(QStringLiteral("pushButton_24"));
        sizePolicy1.setHeightForWidth(pushButton_24->sizePolicy().hasHeightForWidth());
        pushButton_24->setSizePolicy(sizePolicy1);
        pushButton_24->setMinimumSize(QSize(80, 30));
        pushButton_24->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_24);

        pushButton_26 = new QPushButton(layoutWidget1);
        pushButton_26->setObjectName(QStringLiteral("pushButton_26"));
        sizePolicy1.setHeightForWidth(pushButton_26->sizePolicy().hasHeightForWidth());
        pushButton_26->setSizePolicy(sizePolicy1);
        pushButton_26->setMinimumSize(QSize(80, 30));
        pushButton_26->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_26);

        pushButton_25 = new QPushButton(layoutWidget1);
        pushButton_25->setObjectName(QStringLiteral("pushButton_25"));
        sizePolicy1.setHeightForWidth(pushButton_25->sizePolicy().hasHeightForWidth());
        pushButton_25->setSizePolicy(sizePolicy1);
        pushButton_25->setMinimumSize(QSize(80, 30));
        pushButton_25->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_25);

        pushButton_18 = new QPushButton(layoutWidget1);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        sizePolicy1.setHeightForWidth(pushButton_18->sizePolicy().hasHeightForWidth());
        pushButton_18->setSizePolicy(sizePolicy1);
        pushButton_18->setMinimumSize(QSize(80, 30));
        pushButton_18->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_18);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(80, 30));
        pushButton->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton);

        pushButton_15 = new QPushButton(layoutWidget1);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        sizePolicy1.setHeightForWidth(pushButton_15->sizePolicy().hasHeightForWidth());
        pushButton_15->setSizePolicy(sizePolicy1);
        pushButton_15->setMinimumSize(QSize(80, 30));
        pushButton_15->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_15);

        pushButton_22 = new QPushButton(layoutWidget1);
        pushButton_22->setObjectName(QStringLiteral("pushButton_22"));
        sizePolicy1.setHeightForWidth(pushButton_22->sizePolicy().hasHeightForWidth());
        pushButton_22->setSizePolicy(sizePolicy1);
        pushButton_22->setMinimumSize(QSize(80, 30));
        pushButton_22->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_22);

        pushButton_23 = new QPushButton(layoutWidget1);
        pushButton_23->setObjectName(QStringLiteral("pushButton_23"));
        sizePolicy1.setHeightForWidth(pushButton_23->sizePolicy().hasHeightForWidth());
        pushButton_23->setSizePolicy(sizePolicy1);
        pushButton_23->setMinimumSize(QSize(80, 30));
        pushButton_23->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(pushButton_23);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 90, 1000, 600));
        tableWidget->setMinimumSize(QSize(1000, 600));
        tableWidget->setMaximumSize(QSize(1000, 600));
        tableWidget->setSizeIncrement(QSize(0, 0));
        tableWidget->setBaseSize(QSize(0, 0));
        tableWidget->setAcceptDrops(false);
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(560, 50, 380, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_20 = new QPushButton(layoutWidget2);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        sizePolicy1.setHeightForWidth(pushButton_20->sizePolicy().hasHeightForWidth());
        pushButton_20->setSizePolicy(sizePolicy1);
        pushButton_20->setMinimumSize(QSize(120, 30));
        pushButton_20->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(pushButton_20);

        pushButton_21 = new QPushButton(layoutWidget2);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        sizePolicy1.setHeightForWidth(pushButton_21->sizePolicy().hasHeightForWidth());
        pushButton_21->setSizePolicy(sizePolicy1);
        pushButton_21->setMinimumSize(QSize(80, 30));
        pushButton_21->setMaximumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_21);

        PackageManageClass->setCentralWidget(centralWidget);
        layoutWidget->raise();
        tableWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();

        retranslateUi(PackageManageClass);

        QMetaObject::connectSlotsByName(PackageManageClass);
    } // setupUi

    void retranslateUi(QMainWindow *PackageManageClass)
    {
        PackageManageClass->setWindowTitle(QApplication::translate("PackageManageClass", "PackageManage", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("PackageManageClass", "\346\237\245", Q_NULLPTR));
        label->setText(QString());
        version->setText(QApplication::translate("PackageManageClass", "\347\211\210\346\234\254", Q_NULLPTR));
        pushButton_24->setText(QApplication::translate("PackageManageClass", "\345\210\270\345\225\206\346\226\260\345\273\272", Q_NULLPTR));
        pushButton_26->setText(QApplication::translate("PackageManageClass", "\345\210\270\345\225\206\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_25->setText(QApplication::translate("PackageManageClass", "\345\210\270\345\225\206\347\274\226\350\276\221", Q_NULLPTR));
        pushButton_18->setText(QApplication::translate("PackageManageClass", "\346\270\205\347\220\206", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PackageManageClass", "\345\212\240\345\243\263", Q_NULLPTR));
        pushButton_15->setText(QApplication::translate("PackageManageClass", "\344\270\200\344\275\223\346\211\223\345\214\205", Q_NULLPTR));
        pushButton_22->setText(QApplication::translate("PackageManageClass", "\345\215\207\347\272\247\345\214\205\345\210\266\344\275\234", Q_NULLPTR));
        pushButton_23->setText(QApplication::translate("PackageManageClass", "\345\201\234\346\255\242", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("PackageManageClass", "\345\267\245\344\275\234\347\233\256\345\275\225", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("PackageManageClass", "\345\217\221\345\270\203\347\233\256\345\275\225", Q_NULLPTR));
        pushButton_20->setText(QApplication::translate("PackageManageClass", "\345\217\221\345\270\203\346\234\215\345\212\241\345\231\250\344\270\212\344\274\240", Q_NULLPTR));
        pushButton_21->setText(QApplication::translate("PackageManageClass", "360\344\270\212\344\274\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PackageManageClass: public Ui_PackageManageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKAGEMANAGE_H
