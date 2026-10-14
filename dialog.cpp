
#include "dialog.h"

#include <QApplication>
#include <QColorDialog>
#include <QCoreApplication>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFontDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QPageSetupDialog>
#include <QPalette>
#include <QPrintDialog>
#include <QProgressDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QThread>

// ==================================
// 建構函式：建立主視窗
// ==================================

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Qt 內建對話盒展示");
    resize(520, 400);

    QGridLayout *gridLayout = new QGridLayout(this);

    // 建立文字顯示區
    displayTextEdit = new QTextEdit(this);
    displayTextEdit->setText("Qt 標準通用對話盒\n歡迎使用！");

    // 建立九個按鈕
    colorPushBtn = new QPushButton("顏色對話盒", this);
    errorPushBtn = new QPushButton("錯誤訊息盒", this);
    filePushBtn = new QPushButton("檔案對話盒", this);

    fontPushBtn = new QPushButton("字體對話盒", this);
    inputPushBtn = new QPushButton("輸入對話盒", this);
    pagePushBtn = new QPushButton("頁面設定對話盒", this);

    progressPushBtn = new QPushButton("進度對話盒", this);
    printPushBtn = new QPushButton("列印對話盒", this);
    fontColorPushBtn = new QPushButton("字體顏色對話盒", this);

    // ==================================
    // 按鈕排列：3 x 3
    // ==================================

    gridLayout->addWidget(colorPushBtn, 0, 0);
    gridLayout->addWidget(errorPushBtn, 0, 1);
    gridLayout->addWidget(filePushBtn, 0, 2);

    gridLayout->addWidget(fontPushBtn, 1, 0);
    gridLayout->addWidget(inputPushBtn, 1, 1);
    gridLayout->addWidget(pagePushBtn, 1, 2);

    gridLayout->addWidget(progressPushBtn, 2, 0);
    gridLayout->addWidget(printPushBtn, 2, 1);
    gridLayout->addWidget(fontColorPushBtn, 2, 2);

    // 文字框佔據下方三欄
    gridLayout->addWidget(displayTextEdit, 3, 0, 1, 3);

    // ==================================
    // 訊號與槽函式連接
    // ==================================

    connect(colorPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(errorPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(filePushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(fontPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(inputPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(pagePushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(progressPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(printPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);

    connect(fontColorPushBtn, &QPushButton::clicked,
            this, &Dialog::doPushBtn);
}

// ==================================
// 解構函式
// ==================================

Dialog::~Dialog()
{
}

// ==================================
// 按鈕功能
// ==================================

void Dialog::doPushBtn()
{
    QPushButton *btn =
        qobject_cast<QPushButton *>(sender());

    if (!btn)
        return;

    // ==================================
    // 1. 背景顏色對話盒
    // ==================================

    if (btn == colorPushBtn)
    {
        QColor color = QColorDialog::getColor(
            displayTextEdit->palette().color(QPalette::Base),
            this,
            "選擇背景顏色");

        if (color.isValid())
        {
            QPalette palette = displayTextEdit->palette();

            palette.setColor(QPalette::Base, color);

            displayTextEdit->setPalette(palette);
        }
    }

    // ==================================
    // 2. 錯誤訊息盒
    // ==================================

    else if (btn == errorPushBtn)
    {
        QErrorMessage box(this);

        box.setWindowTitle("錯誤訊息盒");

        box.showMessage("這是一個錯誤訊息展示！");

        box.exec();
    }

    // ==================================
    // 3. 檔案對話盒
    // ==================================

    else if (btn == filePushBtn)
    {
        QString fileName =
            QFileDialog::getOpenFileName(
                this,
                "開啟檔案",
                QString(),
                "所有檔案 (*.*);;文字檔案 (*.txt);;C++檔案 (*.cpp *.h)");

        if (!fileName.isEmpty())
        {
            displayTextEdit->setText(fileName);
        }
    }

    // ==================================
    // 4. 字體對話盒
    // ==================================

    else if (btn == fontPushBtn)
    {
        bool ok = false;

        QFont font = QFontDialog::getFont(
            &ok,
            displayTextEdit->font(),
            this,
            "字體對話盒");

        if (ok)
        {
            displayTextEdit->setFont(font);
        }
    }

    // ==================================
    // 5. 輸入對話盒
    // ==================================

    else if (btn == inputPushBtn)
    {
        bool ok = false;

        QString text = QInputDialog::getText(
            this,
            "輸入對話盒",
            "請輸入文字：",
            QLineEdit::Normal,
            "Hello Qt",
            &ok);

        if (ok && !text.isEmpty())
        {
            displayTextEdit->setText(text);
        }
    }

    // ==================================
    // 6. 頁面設定對話盒
    // ==================================

    else if (btn == pagePushBtn)
    {
        QPageSetupDialog dialog(&printer, this);

        dialog.setWindowTitle("頁面設定對話盒");

        dialog.exec();
    }

    // ==================================
    // 7. 進度對話盒
    // ==================================

    else if (btn == progressPushBtn)
    {
        QProgressDialog progress(
            "正在模擬進度...",
            "取消",
            0,
            100,
            this);

        progress.setWindowTitle("進度對話盒");
        progress.setMinimumDuration(0);
        progress.setWindowModality(Qt::WindowModal);

        for (int i = 0; i <= 100; i++)
        {
            progress.setValue(i);

            QCoreApplication::processEvents();

            if (progress.wasCanceled())
            {
                break;
            }

            QThread::msleep(20);
        }

        progress.setValue(100);
    }

    // ==================================
    // 8. 列印對話盒
    // ==================================

    else if (btn == printPushBtn)
    {
        QPrintDialog dialog(&printer, this);

        dialog.setWindowTitle("列印對話盒");

        if (dialog.exec() == QDialog::Accepted)
        {
            displayTextEdit->print(&printer);
        }
    }

    // ==================================
    // 9. 字體顏色對話盒（新增）
    // ==================================

    else if (btn == fontColorPushBtn)
    {
        // 開啟顏色選擇視窗
        QColor color = QColorDialog::getColor(
            displayTextEdit->textColor(),
            this,
            "選擇字體顏色");

        if (color.isValid())
        {
            // 選取文字框內的全部文字
            QTextCursor cursor = displayTextEdit->textCursor();

            cursor.select(QTextCursor::Document);

            // 建立文字顏色格式
            QTextCharFormat format;
            format.setForeground(color);

            // 將全部文字套用新顏色
            cursor.mergeCharFormat(format);

            // 取消選取並將游標移到最後
            cursor.clearSelection();
            cursor.movePosition(QTextCursor::End);

            displayTextEdit->setTextCursor(cursor);

            // 後續輸入的文字也套用新顏色
            displayTextEdit->setTextColor(color);
        }
    }
}
