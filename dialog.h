
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPrinter>

class QTextEdit;
class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private slots:
    void doPushBtn();

private:
    QTextEdit *displayTextEdit;

    QPushButton *colorPushBtn;
    QPushButton *errorPushBtn;
    QPushButton *filePushBtn;
    QPushButton *fontPushBtn;
    QPushButton *inputPushBtn;
    QPushButton *pagePushBtn;
    QPushButton *progressPushBtn;
    QPushButton *printPushBtn;

    // 新增：字體顏色按鈕
    QPushButton *fontColorPushBtn;

    QPrinter printer;
};

#endif // DIALOG_H
