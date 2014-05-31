/********************************************************************************
** Form generated from reading UI file 'tripplanner.ui'
**
** Created: Sat May 31 13:18:33 2014
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

class Ui_TripPlanner
{
public:

    void setupUi(QDialog *TripPlanner)
    {
        if (TripPlanner->objectName().isEmpty())
            TripPlanner->setObjectName(QString::fromUtf8("TripPlanner"));
        TripPlanner->resize(400, 300);

        retranslateUi(TripPlanner);

        QMetaObject::connectSlotsByName(TripPlanner);
    } // setupUi

    void retranslateUi(QDialog *TripPlanner)
    {
        TripPlanner->setWindowTitle(QApplication::translate("TripPlanner", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TripPlanner: public Ui_TripPlanner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIPPLANNER_H
