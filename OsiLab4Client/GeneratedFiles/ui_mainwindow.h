/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QLabel *label_5;
    QTableWidget *TWg;
    QFrame *line_4;
    QComboBox *comboBoxIstok;
    QCheckBox *checkBoxStok;
    QLabel *label;
    QLineEdit *waterName;
    QCheckBox *checkBoxIstok;
    QSpinBox *SqrOfWater;
    QLabel *label_7;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *IsOk;
    QPushButton *Redact;
    QPushButton *btnReturn;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *SqrOfSea;
    QFrame *line_5;
    QComboBox *comboBoxOfLake;
    QLabel *label_6;
    QFrame *line_7;
    QComboBox *comboBoxTypeOfWater;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sort;
    QPushButton *Dlt;
    QPushButton *add;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line;
    QSpinBox *LengthOfRiver;
    QComboBox *comboBoxStok;
    QFrame *line_2;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QFrame *line_6;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(600, 440);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 160, 91, 16));
        TWg = new QTableWidget(centralWidget);
        if (TWg->columnCount() < 2)
            TWg->setColumnCount(2);
        QFont font;
        font.setFamily(QStringLiteral("Segoe Script"));
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        TWg->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe Script"));
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        TWg->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        TWg->setObjectName(QStringLiteral("TWg"));
        TWg->setGeometry(QRect(341, 10, 221, 371));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(10, 200, 321, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        comboBoxIstok = new QComboBox(centralWidget);
        comboBoxIstok->setObjectName(QStringLiteral("comboBoxIstok"));
        comboBoxIstok->setGeometry(QRect(140, 120, 181, 22));
        checkBoxStok = new QCheckBox(centralWidget);
        checkBoxStok->setObjectName(QStringLiteral("checkBoxStok"));
        checkBoxStok->setGeometry(QRect(10, 70, 101, 17));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 71, 16));
        waterName = new QLineEdit(centralWidget);
        waterName->setObjectName(QStringLiteral("waterName"));
        waterName->setGeometry(QRect(10, 20, 231, 20));
        waterName->setMaxLength(20);
        checkBoxIstok = new QCheckBox(centralWidget);
        checkBoxIstok->setObjectName(QStringLiteral("checkBoxIstok"));
        checkBoxIstok->setGeometry(QRect(10, 120, 101, 17));
        SqrOfWater = new QSpinBox(centralWidget);
        SqrOfWater->setObjectName(QStringLiteral("SqrOfWater"));
        SqrOfWater->setGeometry(QRect(10, 280, 311, 22));
        SqrOfWater->setMinimum(1);
        SqrOfWater->setMaximum(100000);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 260, 101, 16));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 320, 310, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        IsOk = new QPushButton(layoutWidget);
        IsOk->setObjectName(QStringLiteral("IsOk"));

        horizontalLayout->addWidget(IsOk);

        Redact = new QPushButton(layoutWidget);
        Redact->setObjectName(QStringLiteral("Redact"));

        horizontalLayout->addWidget(Redact);

        btnReturn = new QPushButton(layoutWidget);
        btnReturn->setObjectName(QStringLiteral("btnReturn"));

        horizontalLayout->addWidget(btnReturn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        SqrOfSea = new QSpinBox(centralWidget);
        SqrOfSea->setObjectName(QStringLiteral("SqrOfSea"));
        SqrOfSea->setGeometry(QRect(10, 280, 311, 22));
        SqrOfSea->setMinimum(10000);
        SqrOfSea->setMaximum(10000000);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 250, 321, 16));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        comboBoxOfLake = new QComboBox(centralWidget);
        comboBoxOfLake->setObjectName(QStringLiteral("comboBoxOfLake"));
        comboBoxOfLake->setEnabled(true);
        comboBoxOfLake->setGeometry(QRect(10, 230, 311, 21));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 210, 81, 16));
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(116, 47, 10, 110));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        comboBoxTypeOfWater = new QComboBox(centralWidget);
        comboBoxTypeOfWater->setObjectName(QStringLiteral("comboBoxTypeOfWater"));
        comboBoxTypeOfWater->setGeometry(QRect(250, 20, 69, 22));
        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(11, 350, 310, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        sort = new QPushButton(layoutWidget_2);
        sort->setObjectName(QStringLiteral("sort"));

        horizontalLayout_2->addWidget(sort);

        Dlt = new QPushButton(layoutWidget_2);
        Dlt->setObjectName(QStringLiteral("Dlt"));

        horizontalLayout_2->addWidget(Dlt);

        add = new QPushButton(layoutWidget_2);
        add->setObjectName(QStringLiteral("add"));

        horizontalLayout_2->addWidget(add);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 40, 321, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        LengthOfRiver = new QSpinBox(centralWidget);
        LengthOfRiver->setObjectName(QStringLiteral("LengthOfRiver"));
        LengthOfRiver->setGeometry(QRect(10, 180, 311, 22));
        LengthOfRiver->setMinimum(1);
        LengthOfRiver->setMaximum(10000);
        comboBoxStok = new QComboBox(centralWidget);
        comboBoxStok->setObjectName(QStringLiteral("comboBoxStok"));
        comboBoxStok->setGeometry(QRect(140, 70, 181, 22));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 150, 321, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 0, 71, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 100, 46, 13));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(150, 50, 46, 13));
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(10, 300, 311, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 20));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
        label_5->setText(QApplication::translate("MainWindowClass", "\320\237\321\200\320\276\321\202\321\217\320\266\320\265\320\275\320\275\320\276\321\201\321\202\321\214", 0));
        QTableWidgetItem *___qtablewidgetitem = TWg->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindowClass", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem1 = TWg->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindowClass", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        comboBoxIstok->clear();
        comboBoxIstok->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Nope", 0)
        );
        checkBoxStok->setText(QApplication::translate("MainWindowClass", "\320\230\320\274\320\265\320\265\321\202\321\201\321\217 \321\201\321\202\320\276\320\272", 0));
        label->setText(QApplication::translate("MainWindowClass", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", 0));
        checkBoxIstok->setText(QApplication::translate("MainWindowClass", "\320\230\320\274\320\265\320\265\321\202\321\201\321\217 \320\270\321\201\321\202\320\276\320\272", 0));
        SqrOfWater->setSuffix(QApplication::translate("MainWindowClass", " \320\272\320\262. \320\272\320\274", 0));
        label_7->setText(QApplication::translate("MainWindowClass", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214", 0));
        IsOk->setText(QApplication::translate("MainWindowClass", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", 0));
        Redact->setText(QApplication::translate("MainWindowClass", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0));
        btnReturn->setText(QApplication::translate("MainWindowClass", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214", 0));
        SqrOfSea->setSuffix(QApplication::translate("MainWindowClass", " \320\272\320\262. \320\272\320\274", 0));
        comboBoxOfLake->clear();
        comboBoxOfLake->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Salt", 0)
         << QApplication::translate("MainWindowClass", "Fresh", 0)
        );
        label_6->setText(QApplication::translate("MainWindowClass", "\320\241\320\276\320\273\321\221\320\275\320\276\321\201\321\202\321\214", 0));
        comboBoxTypeOfWater->clear();
        comboBoxTypeOfWater->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "River", 0)
         << QApplication::translate("MainWindowClass", "Lake", 0)
         << QApplication::translate("MainWindowClass", "Sea", 0)
        );
        sort->setText(QApplication::translate("MainWindowClass", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0));
        Dlt->setText(QApplication::translate("MainWindowClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        add->setText(QApplication::translate("MainWindowClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\20510", 0));
        LengthOfRiver->setSuffix(QApplication::translate("MainWindowClass", " \320\272\320\262. \320\272\320\274", 0));
        comboBoxStok->clear();
        comboBoxStok->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "Nope", 0)
        );
        label_2->setText(QApplication::translate("MainWindowClass", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        label_4->setText(QApplication::translate("MainWindowClass", "\320\230\321\201\321\202\320\276\320\272", 0));
        label_3->setText(QApplication::translate("MainWindowClass", "\320\241\321\202\320\276\320\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
