/********************************************************************************
** Form generated from reading UI file 'AddVer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDVER_H
#define UI_ADDVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddVer
{
public:
    QListView *listView;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *AddVer)
    {
        if (AddVer->objectName().isEmpty())
            AddVer->setObjectName(QStringLiteral("AddVer"));
        AddVer->resize(392, 335);
        listView = new QListView(AddVer);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(10, 10, 256, 301));
        layoutWidget = new QWidget(AddVer);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(300, 40, 77, 83));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        retranslateUi(AddVer);

        QMetaObject::connectSlotsByName(AddVer);
    } // setupUi

    void retranslateUi(QWidget *AddVer)
    {
        AddVer->setWindowTitle(QApplication::translate("AddVer", "AddVer", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AddVer", "\346\226\260\345\242\236", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("AddVer", "\347\274\226\350\276\221", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("AddVer", "\345\210\240\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddVer: public Ui_AddVer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDVER_H
