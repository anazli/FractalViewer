#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

    void updateImageData();

signals:

private:
    QGridLayout *m_grid;
    QLabel *m_imageLabel;
};

#endif // WIDGET_H
