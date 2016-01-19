/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGridLayout *gridLayout;
    QLabel *video;
    QFrame *line_2;
    QFrame *line_4;
    QFrame *line_3;
    QFrame *line;
    QLabel *video3;
    QLabel *video1;
    QLabel *video2;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLineEdit *param_cT;
    QLineEdit *param_alpha;
    QLabel *label_4;
    QLineEdit *param_cF;
    QLabel *label;
    QLabel *label_5;
    QLineEdit *param_framerate;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(919, 501);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(pushButton_2, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        video = new QLabel(centralWidget);
        video->setObjectName(QStringLiteral("video"));
        video->setAutoFillBackground(true);
        video->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(video, 0, 0, 1, 1);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 0, 1, 1, 1);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 2, 1, 1, 1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 2, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        video3 = new QLabel(centralWidget);
        video3->setObjectName(QStringLiteral("video3"));
        sizePolicy.setHeightForWidth(video3->sizePolicy().hasHeightForWidth());
        video3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(video3, 2, 2, 1, 1);

        video1 = new QLabel(centralWidget);
        video1->setObjectName(QStringLiteral("video1"));
        video1->setStyleSheet(QStringLiteral("Border-color: #000;"));

        gridLayout->addWidget(video1, 0, 2, 1, 1);

        video2 = new QLabel(centralWidget);
        video2->setObjectName(QStringLiteral("video2"));

        gridLayout->addWidget(video2, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_3, 0, 4, 1, 1);

        param_cT = new QLineEdit(centralWidget);
        param_cT->setObjectName(QStringLiteral("param_cT"));
        sizePolicy1.setHeightForWidth(param_cT->sizePolicy().hasHeightForWidth());
        param_cT->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(param_cT, 0, 5, 1, 1);

        param_alpha = new QLineEdit(centralWidget);
        param_alpha->setObjectName(QStringLiteral("param_alpha"));
        sizePolicy1.setHeightForWidth(param_alpha->sizePolicy().hasHeightForWidth());
        param_alpha->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(param_alpha, 0, 3, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_4, 0, 2, 1, 1);

        param_cF = new QLineEdit(centralWidget);
        param_cF->setObjectName(QStringLiteral("param_cF"));
        sizePolicy1.setHeightForWidth(param_cF->sizePolicy().hasHeightForWidth());
        param_cF->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(param_cF, 0, 7, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label, 0, 6, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        param_framerate = new QLineEdit(centralWidget);
        param_framerate->setObjectName(QStringLiteral("param_framerate"));
        sizePolicy1.setHeightForWidth(param_framerate->sizePolicy().hasHeightForWidth());
        param_framerate->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(param_framerate, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 919, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gmm", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Load", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Play", 0));
        video->setText(QString());
        video3->setText(QString());
        video1->setText(QString());
        video2->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "cT", 0));
        param_cT->setText(QApplication::translate("MainWindow", "0.05", 0));
        param_alpha->setText(QApplication::translate("MainWindow", "0.002", 0));
        label_4->setText(QApplication::translate("MainWindow", "alpha", 0));
        param_cF->setText(QApplication::translate("MainWindow", "0.1", 0));
        label->setText(QApplication::translate("MainWindow", "cF", 0));
        label_5->setText(QApplication::translate("MainWindow", "frameRate", 0));
        param_framerate->setText(QApplication::translate("MainWindow", "30", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
