/********************************************************************************
** Form generated from reading UI file 'changer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGER_H
#define UI_CHANGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Changer
{
public:
    QLabel *image_label;

    void setupUi(QWidget *Changer)
    {
        if (Changer->objectName().isEmpty())
            Changer->setObjectName(QString::fromUtf8("Changer"));
        Changer->resize(565, 428);
        image_label = new QLabel(Changer);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setGeometry(QRect(76, 32, 421, 301));

        retranslateUi(Changer);

        QMetaObject::connectSlotsByName(Changer);
    } // setupUi

    void retranslateUi(QWidget *Changer)
    {
        Changer->setWindowTitle(QApplication::translate("Changer", "Form", nullptr));
        image_label->setText(QApplication::translate("Changer", "Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Changer: public Ui_Changer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGER_H
