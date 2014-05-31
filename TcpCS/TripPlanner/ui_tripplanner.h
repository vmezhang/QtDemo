/********************************************************************************
** Form generated from reading UI file 'tripplanner.ui'
**
** Created: Fri May 30 19:42:47 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIPPLANNER_H
#define UI_TRIPPLANNER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_tripplanner
{
public:

    void setupUi(QDialog *tripplanner)
    {
        if (tripplanner->objectName().isEmpty())
            tripplanner->setObjectName(QString::fromUtf8("tripplanner"));
        tripplanner->resize(400, 300);

        retranslateUi(tripplanner);

        QMetaObject::connectSlotsByName(tripplanner);
    } // setupUi

    void retranslateUi(QDialog *tripplanner)
    {
        tripplanner->setWindowTitle(QApplication::translate("tripplanner", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class tripplanner: public Ui_tripplanner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIPPLANNER_H
