#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMoveEvent>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Watermark Tech Test");

    watermark = std::make_unique<WatermarkWidget>("蔡姬 MrBeanC", this); // 必须是子窗体 + 内部置顶， 否则全局置顶会影响其他窗口
    watermark->show();

    ui->label->adjustSize();

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        QTimer::singleShot(0, this, [=](){ watermark->raise(); }); // 使水印在最顶层 使用Timer是因为窗口为模态，会阻塞
        QFileDialog::getOpenFileName(this, "Open File", QDir::homePath());
    });
}

Widget::~Widget()
{
    delete ui;
}
