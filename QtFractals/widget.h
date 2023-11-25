#ifndef WIDGET_H
#define WIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Widget(QWidget *parent = nullptr);

  void updateImageData();

 signals:

 private:
  QGridLayout *m_grid;
  QLabel *m_imageLabel;
};

#endif  // WIDGET_H
