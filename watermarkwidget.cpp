#include "watermarkwidget.h"
#include "ui_watermarkwidget.h"
#include <QDebug>
#include <QPainter>
#include <QtMath>

WatermarkWidget::WatermarkWidget(const QString& watermark, QWidget *parent)
    : QWidget(parent), ui(new Ui::WatermarkWidget)
    , watermark(watermark)
{
    ui->setupUi(this);

    // 鼠标穿透 窗体透明
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    // 只有设置了Dialog才能 才能在父窗口之外显示 同时才能覆盖在其他Qialog之上
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);// Dialog or Tool (Popup | Dialog)

    this->parent = parent;
    parent->installEventFilter(this); // 监听父窗口的事件(move resize)

    resize(parent->size());
    raise(); // 使水印在最顶层
}

WatermarkWidget::~WatermarkWidget()
{
    delete ui;
}

void WatermarkWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font = painter.font();
    font.setPointSize(10);
    font.setFamily("Microsoft YaHei");
    painter.setFont(font);
    painter.setPen(QColor(200, 200, 200, 50));

    int textWidth = painter.fontMetrics().horizontalAdvance(this->watermark);
    int textHeight = painter.fontMetrics().height();
    int marginW = 80;
    int marginH = 60; // 斜向间隔
    int angle = -25; // 水印倾斜角度

    // painter.translate(0, 0); // 只能以左上角为原点，否则resize的时候，watermark会位移
    // 旋转坐标系
    painter.rotate(angle);

    // max
    const int diagonal = qSqrt(qPow(this->width(), 2) + qPow(this->height(), 2));
    const int rows = diagonal / (marginH + textHeight);
    const int cols = diagonal / textWidth;

    // 绘制多行水印
    for (int i = -rows; i < rows; ++i) {
        for (int j = -cols; j < cols; ++j) {
            int x = j * (textWidth + marginW);
            x += i * 50; // 斜向偏移
            int y = i * (textHeight + marginH);
            painter.drawText(x, y, this->watermark);
        }
    }
}

bool WatermarkWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == parent) {
        switch (event->type()) {
        case QEvent::Resize:
            resize(parent->size());
            break;
        case QEvent::Move:
            move(parent->pos());
            break;
        default:
            break;
        }
    }
    return false;
}
