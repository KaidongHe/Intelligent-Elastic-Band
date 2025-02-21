/********************************************************************************
** Form generated from reading UI file 'Infowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWINDOW_H
#define UI_INFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Common_wave.h"
#include "mycombobox.h"
#include "qcustomplot.h"
#include "vprogressbars.h"

QT_BEGIN_NAMESPACE

class Ui_infoWindow
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_OverSpeed;
    QLabel *label_OS;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_Powertext;
    QLabel *label_Power;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_Cycletext;
    QLabel *label_Cycle;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_Vlosstext;
    QCustomPlot *QCustom_Vloss;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_10;
    QLabel *label_Forcetext;
    QLabel *label_Force;
    QSpacerItem *verticalSpacer_11;
    CommonWave *Force_Wave;
    vProgressBars *progressBar;
    QVBoxLayout *verticalLayout;
    QLabel *label_Fatiguetext;
    QCustomPlot *QCustom_Averagepower;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacer;
    MyComboBox *devicesComboBox;
    QPushButton *pushButton_Previous;
    QPushButton *pushButton_Next;
    QPushButton *pushButton_SaveData;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_logo;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_Velocitytext;
    QLabel *label_Velocity;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_2;
    QLabel *null_label3;
    QVBoxLayout *verticalLayout_7;
    QLabel *null_label;
    CommonWave *Velocity_Wave;
    QSpacerItem *horizontalSpacer_3;
    QLabel *null_label2;
    QSpacerItem *verticalSpacer_14;

    void setupUi(QWidget *infoWindow)
    {
        if (infoWindow->objectName().isEmpty())
            infoWindow->setObjectName(QString::fromUtf8("infoWindow"));
        infoWindow->resize(938, 1950);
        infoWindow->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(infoWindow);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_4);

        label_OverSpeed = new QLabel(infoWindow);
        label_OverSpeed->setObjectName(QString::fromUtf8("label_OverSpeed"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_OverSpeed->sizePolicy().hasHeightForWidth());
        label_OverSpeed->setSizePolicy(sizePolicy);
        label_OverSpeed->setMinimumSize(QSize(300, 45));
        label_OverSpeed->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_OverSpeed);

        label_OS = new QLabel(infoWindow);
        label_OS->setObjectName(QString::fromUtf8("label_OS"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_OS->sizePolicy().hasHeightForWidth());
        label_OS->setSizePolicy(sizePolicy1);
        label_OS->setMinimumSize(QSize(300, 0));
        label_OS->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_OS);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalSpacer_5 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_8->addItem(verticalSpacer_5);

        label_Powertext = new QLabel(infoWindow);
        label_Powertext->setObjectName(QString::fromUtf8("label_Powertext"));
        sizePolicy.setHeightForWidth(label_Powertext->sizePolicy().hasHeightForWidth());
        label_Powertext->setSizePolicy(sizePolicy);
        label_Powertext->setMinimumSize(QSize(0, 45));
        label_Powertext->setMaximumSize(QSize(16777215, 45));
        label_Powertext->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_Powertext);

        label_Power = new QLabel(infoWindow);
        label_Power->setObjectName(QString::fromUtf8("label_Power"));
        sizePolicy1.setHeightForWidth(label_Power->sizePolicy().hasHeightForWidth());
        label_Power->setSizePolicy(sizePolicy1);
        label_Power->setMinimumSize(QSize(300, 0));
        label_Power->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_Power);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_8->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout_8, 0, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_6 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_5->addItem(verticalSpacer_6);

        label_Cycletext = new QLabel(infoWindow);
        label_Cycletext->setObjectName(QString::fromUtf8("label_Cycletext"));
        sizePolicy.setHeightForWidth(label_Cycletext->sizePolicy().hasHeightForWidth());
        label_Cycletext->setSizePolicy(sizePolicy);
        label_Cycletext->setMinimumSize(QSize(0, 45));
        label_Cycletext->setMaximumSize(QSize(16777215, 45));
        label_Cycletext->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_Cycletext);

        label_Cycle = new QLabel(infoWindow);
        label_Cycle->setObjectName(QString::fromUtf8("label_Cycle"));
        sizePolicy1.setHeightForWidth(label_Cycle->sizePolicy().hasHeightForWidth());
        label_Cycle->setSizePolicy(sizePolicy1);
        label_Cycle->setMinimumSize(QSize(300, 0));
        label_Cycle->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_Cycle);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_5->addItem(verticalSpacer_3);


        gridLayout->addLayout(verticalLayout_5, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 4, 0, 1, 2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_Vlosstext = new QLabel(infoWindow);
        label_Vlosstext->setObjectName(QString::fromUtf8("label_Vlosstext"));
        sizePolicy1.setHeightForWidth(label_Vlosstext->sizePolicy().hasHeightForWidth());
        label_Vlosstext->setSizePolicy(sizePolicy1);
        label_Vlosstext->setMinimumSize(QSize(0, 45));
        label_Vlosstext->setMaximumSize(QSize(16777215, 45));
        label_Vlosstext->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_Vlosstext);

        QCustom_Vloss = new QCustomPlot(infoWindow);
        QCustom_Vloss->setObjectName(QString::fromUtf8("QCustom_Vloss"));

        verticalLayout_6->addWidget(QCustom_Vloss);


        gridLayout_2->addLayout(verticalLayout_6, 5, 0, 1, 2);

        verticalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer_8, 8, 0, 1, 2);

        verticalSpacer_13 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer_13, 6, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_10);

        label_Forcetext = new QLabel(infoWindow);
        label_Forcetext->setObjectName(QString::fromUtf8("label_Forcetext"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(168);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_Forcetext->sizePolicy().hasHeightForWidth());
        label_Forcetext->setSizePolicy(sizePolicy2);
        label_Forcetext->setLayoutDirection(Qt::LeftToRight);
        label_Forcetext->setStyleSheet(QString::fromUtf8(""));
        label_Forcetext->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_Forcetext);

        label_Force = new QLabel(infoWindow);
        label_Force->setObjectName(QString::fromUtf8("label_Force"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(168);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_Force->sizePolicy().hasHeightForWidth());
        label_Force->setSizePolicy(sizePolicy3);
        label_Force->setMinimumSize(QSize(300, 0));
        label_Force->setStyleSheet(QString::fromUtf8(""));
        label_Force->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_Force);

        verticalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_11);


        horizontalLayout_3->addLayout(verticalLayout_4);

        Force_Wave = new CommonWave(infoWindow);
        Force_Wave->setObjectName(QString::fromUtf8("Force_Wave"));
        sizePolicy1.setHeightForWidth(Force_Wave->sizePolicy().hasHeightForWidth());
        Force_Wave->setSizePolicy(sizePolicy1);
        Force_Wave->setMinimumSize(QSize(0, 0));
        progressBar = new vProgressBars(Force_Wave);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 150, 658, 81));
        progressBar->setValue(24);

        horizontalLayout_3->addWidget(Force_Wave);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_Fatiguetext = new QLabel(infoWindow);
        label_Fatiguetext->setObjectName(QString::fromUtf8("label_Fatiguetext"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(50);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_Fatiguetext->sizePolicy().hasHeightForWidth());
        label_Fatiguetext->setSizePolicy(sizePolicy4);
        label_Fatiguetext->setMinimumSize(QSize(300, 0));
        label_Fatiguetext->setMaximumSize(QSize(16777215, 45));
        label_Fatiguetext->setStyleSheet(QString::fromUtf8(""));
        label_Fatiguetext->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_Fatiguetext);

        QCustom_Averagepower = new QCustomPlot(infoWindow);
        QCustom_Averagepower->setObjectName(QString::fromUtf8("QCustom_Averagepower"));

        verticalLayout->addWidget(QCustom_Averagepower);


        gridLayout_2->addLayout(verticalLayout, 7, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spacer = new QSpacerItem(3000, 50, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer);

        devicesComboBox = new MyComboBox(infoWindow);
        devicesComboBox->setObjectName(QString::fromUtf8("devicesComboBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(devicesComboBox->sizePolicy().hasHeightForWidth());
        devicesComboBox->setSizePolicy(sizePolicy5);
        devicesComboBox->setMinimumSize(QSize(150, 60));
        devicesComboBox->setMaximumSize(QSize(200, 90));
        devicesComboBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(devicesComboBox);

        pushButton_Previous = new QPushButton(infoWindow);
        pushButton_Previous->setObjectName(QString::fromUtf8("pushButton_Previous"));
        sizePolicy5.setHeightForWidth(pushButton_Previous->sizePolicy().hasHeightForWidth());
        pushButton_Previous->setSizePolicy(sizePolicy5);
        pushButton_Previous->setMinimumSize(QSize(150, 60));
        pushButton_Previous->setMaximumSize(QSize(16777215, 70));

        horizontalLayout->addWidget(pushButton_Previous);

        pushButton_Next = new QPushButton(infoWindow);
        pushButton_Next->setObjectName(QString::fromUtf8("pushButton_Next"));
        sizePolicy5.setHeightForWidth(pushButton_Next->sizePolicy().hasHeightForWidth());
        pushButton_Next->setSizePolicy(sizePolicy5);
        pushButton_Next->setMinimumSize(QSize(150, 60));
        pushButton_Next->setMaximumSize(QSize(16777215, 70));

        horizontalLayout->addWidget(pushButton_Next);

        pushButton_SaveData = new QPushButton(infoWindow);
        pushButton_SaveData->setObjectName(QString::fromUtf8("pushButton_SaveData"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_SaveData->sizePolicy().hasHeightForWidth());
        pushButton_SaveData->setSizePolicy(sizePolicy6);
        pushButton_SaveData->setMinimumSize(QSize(150, 50));
        pushButton_SaveData->setMaximumSize(QSize(16777215, 70));

        horizontalLayout->addWidget(pushButton_SaveData);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 9, 0, 1, 2);

        label_logo = new QLabel(infoWindow);
        label_logo->setObjectName(QString::fromUtf8("label_logo"));
        QSizePolicy sizePolicy7(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_logo->sizePolicy().hasHeightForWidth());
        label_logo->setSizePolicy(sizePolicy7);
        label_logo->setMinimumSize(QSize(0, 20));
        label_logo->setMaximumSize(QSize(300, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(16);
        label_logo->setFont(font);
        label_logo->setStyleSheet(QString::fromUtf8(""));
        label_logo->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_logo, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_9);

        label_Velocitytext = new QLabel(infoWindow);
        label_Velocitytext->setObjectName(QString::fromUtf8("label_Velocitytext"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_Velocitytext->sizePolicy().hasHeightForWidth());
        label_Velocitytext->setSizePolicy(sizePolicy8);
        label_Velocitytext->setLayoutDirection(Qt::LeftToRight);
        label_Velocitytext->setStyleSheet(QString::fromUtf8(""));
        label_Velocitytext->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_Velocitytext);

        label_Velocity = new QLabel(infoWindow);
        label_Velocity->setObjectName(QString::fromUtf8("label_Velocity"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(label_Velocity->sizePolicy().hasHeightForWidth());
        label_Velocity->setSizePolicy(sizePolicy9);
        label_Velocity->setMinimumSize(QSize(300, 0));
        label_Velocity->setStyleSheet(QString::fromUtf8(""));
        label_Velocity->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_Velocity);

        verticalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_12);


        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        null_label3 = new QLabel(infoWindow);
        null_label3->setObjectName(QString::fromUtf8("null_label3"));

        horizontalLayout_2->addWidget(null_label3);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        null_label = new QLabel(infoWindow);
        null_label->setObjectName(QString::fromUtf8("null_label"));
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(null_label->sizePolicy().hasHeightForWidth());
        null_label->setSizePolicy(sizePolicy10);
        null_label->setMinimumSize(QSize(0, 100));

        verticalLayout_7->addWidget(null_label);

        Velocity_Wave = new CommonWave(infoWindow);
        Velocity_Wave->setObjectName(QString::fromUtf8("Velocity_Wave"));
        sizePolicy1.setHeightForWidth(Velocity_Wave->sizePolicy().hasHeightForWidth());
        Velocity_Wave->setSizePolicy(sizePolicy1);
        Velocity_Wave->setMinimumSize(QSize(0, 0));

        verticalLayout_7->addWidget(Velocity_Wave);


        horizontalLayout_2->addLayout(verticalLayout_7);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        null_label2 = new QLabel(infoWindow);
        null_label2->setObjectName(QString::fromUtf8("null_label2"));

        horizontalLayout_2->addWidget(null_label2);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 0, 1, 2);

        verticalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer_14, 0, 0, 1, 1);


        retranslateUi(infoWindow);

        QMetaObject::connectSlotsByName(infoWindow);
    } // setupUi

    void retranslateUi(QWidget *infoWindow)
    {
        infoWindow->setWindowTitle(QCoreApplication::translate("infoWindow", "Form", nullptr));
        label_OverSpeed->setText(QCoreApplication::translate("infoWindow", "Overspeed", nullptr));
        label_OS->setText(QCoreApplication::translate("infoWindow", "\342\200\224 \342\200\224", nullptr));
        label_Powertext->setText(QCoreApplication::translate("infoWindow", "AveragePower", nullptr));
        label_Power->setText(QCoreApplication::translate("infoWindow", "\342\200\224 \342\200\224", nullptr));
        label_Cycletext->setText(QCoreApplication::translate("infoWindow", "Cycle", nullptr));
        label_Cycle->setText(QCoreApplication::translate("infoWindow", "\342\200\224 \342\200\224", nullptr));
        label_Vlosstext->setText(QCoreApplication::translate("infoWindow", "  Vloss (%)", nullptr));
        label_Forcetext->setText(QCoreApplication::translate("infoWindow", " Tension (N)", nullptr));
        label_Force->setText(QCoreApplication::translate("infoWindow", " \342\200\224", nullptr));
        label_Fatiguetext->setText(QCoreApplication::translate("infoWindow", "  Average Power (W)", nullptr));
        pushButton_Previous->setText(QCoreApplication::translate("infoWindow", "Preview", nullptr));
        pushButton_Next->setText(QCoreApplication::translate("infoWindow", "Next", nullptr));
        pushButton_SaveData->setText(QCoreApplication::translate("infoWindow", "Save", nullptr));
        label_logo->setText(QCoreApplication::translate("infoWindow", " My Activity ", nullptr));
        label_Velocitytext->setText(QCoreApplication::translate("infoWindow", " V (m/s)", nullptr));
        label_Velocity->setText(QCoreApplication::translate("infoWindow", " \342\200\224", nullptr));
        null_label3->setText(QString());
        null_label->setText(QString());
        null_label2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class infoWindow: public Ui_infoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWINDOW_H
