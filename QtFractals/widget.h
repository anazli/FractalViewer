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

 private slots:
  void genImageButtonClicked();
  void realSpinboxValueChanged(double d);
  void imgSpinboxValueChanged(double d);

 private:
  QGridLayout *m_grid;
  QLabel *m_imageLabel;
  int m_imageWidth = 500;
  int m_imageHeight = 500;
  double m_realNumber = 0.;
  double m_imgNumber = 0.;

  void setupGrid();
};

#endif  // WIDGET_H
