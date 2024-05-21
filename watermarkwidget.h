#ifndef WATERMARKWIDGET_H
#define WATERMARKWIDGET_H

#include <QWidget>

namespace Ui {
class WatermarkWidget;
}

class WatermarkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WatermarkWidget(const QString& watermark = "Watermark", QWidget *parent = nullptr);
    ~WatermarkWidget();

private:
    Ui::WatermarkWidget *ui;

    QWidget* parent = nullptr;
    QString watermark;;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // WATERMARKWIDGET_H
