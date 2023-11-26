#ifndef WIDGET_H
#define WIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Widget(QWidget *parent = nullptr, int imWidth = 500,
                  int imHeight = 500);

  void updateImageData();

 private slots:
  void buttonClicked();

 private:
  QGridLayout *m_grid;
  QLabel *m_imageLabel;
  int m_imageWidth;
  int m_imageHeight;
};

#endif  // WIDGET_H
