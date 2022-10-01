/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QLabel *label_2;
    QSpinBox *spinbox_rotate_x;
    QLabel *label_3;
    QSpinBox *spinbox_rotate_y;
    QLabel *label_4;
    QSpinBox *spinbox_rotate_z;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *formLayout_4;
    QLabel *label;
    QDoubleSpinBox *spinbox_scale;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_14;
    QFormLayout *formLayout_2;
    QLabel *label_15;
    QSpinBox *spinbox_width_landscape;
    QSpinBox *spinbox_height_landscape;
    QLabel *label_16;
    QLabel *label_5;
    QFormLayout *formLayout_3;
    QLabel *label_6;
    QSpinBox *spinbox_octaves;
    QLabel *label_10;
    QDoubleSpinBox *spinbox_gain;
    QLabel *label_11;
    QDoubleSpinBox *spinbox_lacunarity;
    QLabel *label_8;
    QFormLayout *formLayout_6;
    QLabel *label_7;
    QSpinBox *spinbox_seed;
    QLabel *label_9;
    QDoubleSpinBox *spinbox_frequency;
    QSpacerItem *verticalSpacer;
    QPushButton *black_white_color;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_23;
    QFormLayout *formLayout_5;
    QLabel *label_20;
    QSpinBox *spinbox_light_position_x;
    QLabel *label_21;
    QSpinBox *spinbox_light_position_y;
    QLabel *label_22;
    QSpinBox *spinbox_light_position_z;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1146, 834);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(3);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, -1, 0, -1);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(218, 0));
        tabWidget->setMaximumSize(QSize(218, 16777215));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setMinimumSize(QSize(220, 0));
        tab->setMaximumSize(QSize(220, 16777215));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(4, 10, 0, -1);
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        spinbox_rotate_x = new QSpinBox(tab_3);
        spinbox_rotate_x->setObjectName(QString::fromUtf8("spinbox_rotate_x"));
        spinbox_rotate_x->setMinimumSize(QSize(50, 0));
        spinbox_rotate_x->setMaximumSize(QSize(50, 16777215));
        spinbox_rotate_x->setMinimum(-360);
        spinbox_rotate_x->setMaximum(360);
        spinbox_rotate_x->setValue(50);
        spinbox_rotate_x->setDisplayIntegerBase(10);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinbox_rotate_x);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        spinbox_rotate_y = new QSpinBox(tab_3);
        spinbox_rotate_y->setObjectName(QString::fromUtf8("spinbox_rotate_y"));
        spinbox_rotate_y->setMinimumSize(QSize(50, 0));
        spinbox_rotate_y->setMaximumSize(QSize(50, 16777215));
        spinbox_rotate_y->setMinimum(-360);
        spinbox_rotate_y->setMaximum(360);
        spinbox_rotate_y->setValue(0);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinbox_rotate_y);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        spinbox_rotate_z = new QSpinBox(tab_3);
        spinbox_rotate_z->setObjectName(QString::fromUtf8("spinbox_rotate_z"));
        spinbox_rotate_z->setMinimumSize(QSize(50, 0));
        spinbox_rotate_z->setMaximumSize(QSize(50, 50));
        spinbox_rotate_z->setMinimum(-360);
        spinbox_rotate_z->setMaximum(360);
        spinbox_rotate_z->setValue(0);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinbox_rotate_z);


        verticalLayout_4->addLayout(formLayout);

        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_5 = new QVBoxLayout(tab_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label);

        spinbox_scale = new QDoubleSpinBox(tab_4);
        spinbox_scale->setObjectName(QString::fromUtf8("spinbox_scale"));
        spinbox_scale->setMaximumSize(QSize(60, 16777215));
        spinbox_scale->setMinimum(0.100000000000000);
        spinbox_scale->setMaximum(2.800000000000000);
        spinbox_scale->setSingleStep(0.100000000000000);
        spinbox_scale->setValue(1.000000000000000);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, spinbox_scale);


        verticalLayout_5->addLayout(formLayout_4);

        tabWidget_2->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget_2);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_2);

        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(200, 16777215));

        verticalLayout_2->addWidget(label_14);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(6, 8, 29, 37);
        label_15 = new QLabel(tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_15);

        spinbox_width_landscape = new QSpinBox(tab);
        spinbox_width_landscape->setObjectName(QString::fromUtf8("spinbox_width_landscape"));
        spinbox_width_landscape->setMaximumSize(QSize(60, 16777215));
        spinbox_width_landscape->setMinimum(1);
        spinbox_width_landscape->setMaximum(200);
        spinbox_width_landscape->setValue(100);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinbox_width_landscape);

        spinbox_height_landscape = new QSpinBox(tab);
        spinbox_height_landscape->setObjectName(QString::fromUtf8("spinbox_height_landscape"));
        spinbox_height_landscape->setMaximumSize(QSize(60, 16777215));
        spinbox_height_landscape->setMinimum(5);
        spinbox_height_landscape->setMaximum(200);
        spinbox_height_landscape->setValue(100);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, spinbox_height_landscape);

        label_16 = new QLabel(tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_16);


        verticalLayout_2->addLayout(formLayout_2);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(200, 50));

        verticalLayout_2->addWidget(label_5);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setContentsMargins(3, 11, 1, 9);
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_6);

        spinbox_octaves = new QSpinBox(tab);
        spinbox_octaves->setObjectName(QString::fromUtf8("spinbox_octaves"));
        spinbox_octaves->setMaximumSize(QSize(60, 16777215));
        spinbox_octaves->setMinimum(1);
        spinbox_octaves->setMaximum(10);
        spinbox_octaves->setValue(1);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, spinbox_octaves);

        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_10);

        spinbox_gain = new QDoubleSpinBox(tab);
        spinbox_gain->setObjectName(QString::fromUtf8("spinbox_gain"));
        spinbox_gain->setMinimumSize(QSize(60, 0));
        spinbox_gain->setMaximumSize(QSize(60, 16777215));
        spinbox_gain->setMaximum(5.000000000000000);
        spinbox_gain->setSingleStep(0.100000000000000);
        spinbox_gain->setValue(0.250000000000000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, spinbox_gain);

        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_11);

        spinbox_lacunarity = new QDoubleSpinBox(tab);
        spinbox_lacunarity->setObjectName(QString::fromUtf8("spinbox_lacunarity"));
        spinbox_lacunarity->setMaximumSize(QSize(60, 16777215));
        spinbox_lacunarity->setMaximum(10.000000000000000);
        spinbox_lacunarity->setSingleStep(0.100000000000000);
        spinbox_lacunarity->setValue(2.000000000000000);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, spinbox_lacunarity);


        verticalLayout_2->addLayout(formLayout_3);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        formLayout_6->setContentsMargins(-1, -1, -1, 34);
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_7);

        spinbox_seed = new QSpinBox(tab);
        spinbox_seed->setObjectName(QString::fromUtf8("spinbox_seed"));
        spinbox_seed->setMaximumSize(QSize(200, 16777215));
        spinbox_seed->setMinimum(1);
        spinbox_seed->setMaximum(10000);
        spinbox_seed->setValue(28);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, spinbox_seed);

        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label_9);

        spinbox_frequency = new QDoubleSpinBox(tab);
        spinbox_frequency->setObjectName(QString::fromUtf8("spinbox_frequency"));
        spinbox_frequency->setMinimum(0.000000000000000);
        spinbox_frequency->setMaximum(5.000000000000000);
        spinbox_frequency->setSingleStep(0.100000000000000);
        spinbox_frequency->setValue(1.000000000000000);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, spinbox_frequency);


        verticalLayout_2->addLayout(formLayout_6);

        verticalSpacer = new QSpacerItem(20, 42, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_2->addItem(verticalSpacer);

        black_white_color = new QPushButton(tab);
        black_white_color->setObjectName(QString::fromUtf8("black_white_color"));

        verticalLayout_2->addWidget(black_white_color);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setMinimumSize(QSize(220, 0));
        tab_2->setMaximumSize(QSize(220, 16777215));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_23 = new QLabel(tab_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setMaximumSize(QSize(200, 50));

        verticalLayout_3->addWidget(label_23);

        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        formLayout_5->setContentsMargins(4, 12, 0, -1);
        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMaximumSize(QSize(50, 16777215));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_20);

        spinbox_light_position_x = new QSpinBox(tab_2);
        spinbox_light_position_x->setObjectName(QString::fromUtf8("spinbox_light_position_x"));
        spinbox_light_position_x->setMinimumSize(QSize(50, 0));
        spinbox_light_position_x->setMaximumSize(QSize(50, 16777215));
        spinbox_light_position_x->setMinimum(1);
        spinbox_light_position_x->setMaximum(2000);
        spinbox_light_position_x->setSingleStep(100);
        spinbox_light_position_x->setValue(150);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, spinbox_light_position_x);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_21);

        spinbox_light_position_y = new QSpinBox(tab_2);
        spinbox_light_position_y->setObjectName(QString::fromUtf8("spinbox_light_position_y"));
        spinbox_light_position_y->setMinimumSize(QSize(50, 0));
        spinbox_light_position_y->setMaximumSize(QSize(50, 16777215));
        spinbox_light_position_y->setMinimum(1);
        spinbox_light_position_y->setMaximum(2000);
        spinbox_light_position_y->setSingleStep(100);
        spinbox_light_position_y->setValue(100);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, spinbox_light_position_y);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_22);

        spinbox_light_position_z = new QSpinBox(tab_2);
        spinbox_light_position_z->setObjectName(QString::fromUtf8("spinbox_light_position_z"));
        spinbox_light_position_z->setMinimumSize(QSize(50, 0));
        spinbox_light_position_z->setMaximumSize(QSize(50, 50));
        spinbox_light_position_z->setMinimum(1);
        spinbox_light_position_z->setMaximum(2000);
        spinbox_light_position_z->setSingleStep(100);
        spinbox_light_position_z->setValue(150);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, spinbox_light_position_z);


        verticalLayout_3->addLayout(formLayout_5);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1146, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200\321\213 \320\273\320\260\320\275\320\264\321\210\320\260\321\204\321\202\320\260", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\260", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270\n"
"\320\273\320\260\320\275\320\264\321\210\320\260\321\204\321\202\320\260", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\236\320\272\321\202\320\260\320\262\321\213", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\320\276\321\217\320\275\321\201\321\202\320\262\320\276", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\233\320\260\320\272\321\203\320\275\320\260\321\200\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \n"
" \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\227\320\265\321\200\320\275\320\276", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260", nullptr));
        black_white_color->setText(QCoreApplication::translate("MainWindow", "\320\247\320\265\321\200\320\275\320\276-\320\261\320\265\320\273\321\213\320\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\233\320\260\320\275\320\264\321\210\320\260\321\204\321\202", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\267\320\270\321\206\320\270\321\217 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260\n"
"\320\276\321\201\320\262\320\265\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "z", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\236\321\201\320\262\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
