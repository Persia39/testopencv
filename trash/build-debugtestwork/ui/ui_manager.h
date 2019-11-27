/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Manager
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *image_label;
    QVBoxLayout *verticalLayout;
    QPushButton *up_button;
    QHBoxLayout *horizontalLayout;
    QPushButton *left_button;
    QPushButton *right_button;
    QPushButton *button_open;

    void setupUi(QWidget *Manager)
    {
        if (Manager->objectName().isEmpty())
            Manager->setObjectName(QString::fromUtf8("Manager"));
        Manager->resize(812, 507);
        verticalLayout_2 = new QVBoxLayout(Manager);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        image_label = new QLabel(Manager);
        image_label->setObjectName(QString::fromUtf8("image_label"));

        verticalLayout_2->addWidget(image_label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        up_button = new QPushButton(Manager);
        up_button->setObjectName(QString::fromUtf8("up_button"));

        verticalLayout->addWidget(up_button);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        left_button = new QPushButton(Manager);
        left_button->setObjectName(QString::fromUtf8("left_button"));

        horizontalLayout->addWidget(left_button);

        right_button = new QPushButton(Manager);
        right_button->setObjectName(QString::fromUtf8("right_button"));

        horizontalLayout->addWidget(right_button);


        verticalLayout->addLayout(horizontalLayout);

        button_open = new QPushButton(Manager);
        button_open->setObjectName(QString::fromUtf8("button_open"));

        verticalLayout->addWidget(button_open);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Manager);

        QMetaObject::connectSlotsByName(Manager);
    } // setupUi

    void retranslateUi(QWidget *Manager)
    {
        Manager->setWindowTitle(QApplication::translate("Manager", "Form", nullptr));
        image_label->setText(QApplication::translate("Manager", "TextLabel", nullptr));
        up_button->setText(QApplication::translate("Manager", "Up", nullptr));
        left_button->setText(QApplication::translate("Manager", "Left", nullptr));
        right_button->setText(QApplication::translate("Manager", "Right", nullptr));
        button_open->setText(QApplication::translate("Manager", "Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Manager: public Ui_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
