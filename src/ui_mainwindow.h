/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QSpinBox *snapshotSpinBox;
    QLabel *label_8;
    QLabel *numberSnapshotLabel;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSlider *snapshotSlider;
    QGridLayout *gridLayout_3;
    QLabel *numVerticesLabel;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_4;
    QComboBox *sourceComboBox;
    QLabel *label;
    QDoubleSpinBox *ubiRangeSpinBox;
    QLabel *numEdgesLabel;
    QLabel *timeLabel;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(832, 624);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        snapshotSpinBox = new QSpinBox(centralWidget);
        snapshotSpinBox->setObjectName(QString::fromUtf8("snapshotSpinBox"));

        horizontalLayout_4->addWidget(snapshotSpinBox);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);

        numberSnapshotLabel = new QLabel(centralWidget);
        numberSnapshotLabel->setObjectName(QString::fromUtf8("numberSnapshotLabel"));

        horizontalLayout_4->addWidget(numberSnapshotLabel);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);


        verticalLayout_6->addLayout(horizontalLayout_4);

        snapshotSlider = new QSlider(centralWidget);
        snapshotSlider->setObjectName(QString::fromUtf8("snapshotSlider"));
        snapshotSlider->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(snapshotSlider);


        horizontalLayout_3->addLayout(verticalLayout_6);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        numVerticesLabel = new QLabel(centralWidget);
        numVerticesLabel->setObjectName(QString::fromUtf8("numVerticesLabel"));

        gridLayout_3->addWidget(numVerticesLabel, 2, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 4, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        sourceComboBox = new QComboBox(centralWidget);
        sourceComboBox->setObjectName(QString::fromUtf8("sourceComboBox"));

        gridLayout_3->addWidget(sourceComboBox, 0, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        ubiRangeSpinBox = new QDoubleSpinBox(centralWidget);
        ubiRangeSpinBox->setObjectName(QString::fromUtf8("ubiRangeSpinBox"));

        gridLayout_3->addWidget(ubiRangeSpinBox, 1, 1, 1, 1);

        numEdgesLabel = new QLabel(centralWidget);
        numEdgesLabel->setObjectName(QString::fromUtf8("numEdgesLabel"));

        gridLayout_3->addWidget(numEdgesLabel, 3, 1, 1, 1);

        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));

        gridLayout_3->addWidget(timeLabel, 4, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 5, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 832, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "of", 0, QApplication::UnicodeUTF8));
        numberSnapshotLabel->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Snapshots", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        numVerticesLabel->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Ubisense range", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Time:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Number Vertices", 0, QApplication::UnicodeUTF8));
        sourceComboBox->clear();
        sourceComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "badges", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "ubisense", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "combined", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("MainWindow", "Data Source:", 0, QApplication::UnicodeUTF8));
        numEdgesLabel->setText(QString());
        timeLabel->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "Number Edges", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
