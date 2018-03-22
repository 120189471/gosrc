/********************************************************************************
** Form generated from reading UI file 'QsInfoGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSINFOGUI_H
#define UI_QSINFOGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QsInfoGUI
{
public:
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_9;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_5;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_7;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *QsInfoGUI)
    {
        if (QsInfoGUI->objectName().isEmpty())
            QsInfoGUI->setObjectName(QStringLiteral("QsInfoGUI"));
        QsInfoGUI->resize(300, 200);
        QsInfoGUI->setMinimumSize(QSize(300, 200));
        QsInfoGUI->setMaximumSize(QSize(300, 200));
        horizontalLayout_13 = new QHBoxLayout(QsInfoGUI);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(QsInfoGUI);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(QsInfoGUI);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(QsInfoGUI);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(QsInfoGUI);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        label_9 = new QLabel(QsInfoGUI);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox_3 = new QCheckBox(QsInfoGUI);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        horizontalLayout_3->addWidget(checkBox_3);


        horizontalLayout_9->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

        horizontalLayout_9->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkBox_5 = new QCheckBox(QsInfoGUI);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        horizontalLayout_5->addWidget(checkBox_5);


        horizontalLayout_10->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        checkBox = new QCheckBox(QsInfoGUI);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_6->addWidget(checkBox);


        horizontalLayout_10->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkBox_7 = new QCheckBox(QsInfoGUI);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        horizontalLayout_7->addWidget(checkBox_7);


        horizontalLayout_11->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        checkBox_2 = new QCheckBox(QsInfoGUI);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_8->addWidget(checkBox_2);


        horizontalLayout_11->addLayout(horizontalLayout_8);


        verticalLayout->addLayout(horizontalLayout_11);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer);

        pushButton = new QPushButton(QsInfoGUI);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_12->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(QsInfoGUI);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_12->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_12);


        horizontalLayout_13->addLayout(verticalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);


        retranslateUi(QsInfoGUI);
        QObject::connect(pushButton, SIGNAL(clicked()), QsInfoGUI, SLOT(saveqsinfo()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), QsInfoGUI, SLOT(close()));

        QMetaObject::connectSlotsByName(QsInfoGUI);
    } // setupUi

    void retranslateUi(QWidget *QsInfoGUI)
    {
        QsInfoGUI->setWindowTitle(QApplication::translate("QsInfoGUI", "QsInfoGUI", Q_NULLPTR));
        label->setText(QApplication::translate("QsInfoGUI", "\345\210\270\345\225\206\345\220\215\347\247\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("QsInfoGUI", "\345\210\270\345\225\206\347\274\226\345\217\267", Q_NULLPTR));
        label_9->setText(QApplication::translate("QsInfoGUI", "\346\225\260\345\255\227\350\214\203\345\233\2640~65535", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("QsInfoGUI", "\346\250\241\346\213\237\347\211\210", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("QsInfoGUI", "\344\273\277\347\234\237\347\211\210", Q_NULLPTR));
        checkBox->setText(QApplication::translate("QsInfoGUI", "\344\273\277\347\234\237\347\213\254\347\253\213\345\256\211\350\243\205\345\214\205", Q_NULLPTR));
        checkBox_7->setText(QApplication::translate("QsInfoGUI", "\347\224\237\344\272\247\347\211\210", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("QsInfoGUI", "\347\224\237\344\272\247\347\213\254\347\253\213\345\256\211\350\243\205\345\214\205", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QsInfoGUI", "\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QsInfoGUI", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QsInfoGUI: public Ui_QsInfoGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSINFOGUI_H
