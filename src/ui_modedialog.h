/********************************************************************************
** Form generated from reading UI file 'modedialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEDIALOG_H
#define UI_MODEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModeDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *realTimeButton;
    QPushButton *loadButton;

    void setupUi(QDialog *ModeDialog)
    {
        if (ModeDialog->objectName().isEmpty())
            ModeDialog->setObjectName(QString::fromUtf8("ModeDialog"));
        ModeDialog->resize(510, 113);
        verticalLayoutWidget = new QWidget(ModeDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(4, 9, 501, 91));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label, 0, Qt::AlignHCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        realTimeButton = new QPushButton(verticalLayoutWidget);
        realTimeButton->setObjectName(QString::fromUtf8("realTimeButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(realTimeButton->sizePolicy().hasHeightForWidth());
        realTimeButton->setSizePolicy(sizePolicy);
        realTimeButton->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(realTimeButton);

        loadButton = new QPushButton(verticalLayoutWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        sizePolicy.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy);
        loadButton->setMinimumSize(QSize(200, 0));

        horizontalLayout_2->addWidget(loadButton);


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(ModeDialog);

        QMetaObject::connectSlotsByName(ModeDialog);
    } // setupUi

    void retranslateUi(QDialog *ModeDialog)
    {
        ModeDialog->setWindowTitle(QApplication::translate("ModeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ModeDialog", "Choose mode:", 0, QApplication::UnicodeUTF8));
        realTimeButton->setText(QApplication::translate("ModeDialog", "Real-time", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("ModeDialog", "Load prerecorded session", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModeDialog: public Ui_ModeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEDIALOG_H
