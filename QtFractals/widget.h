#ifndef WIDGET_H
#define WIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
 public:
  explicit Widget(QWidget *parent = nullptr);

  void CreateMdlbrotSet();
  void CreateJuliaSet();

 private slots:
  void genImageButtonClicked();
  void realSpinboxValueChanged(double d);
  void imgSpinboxValueChanged(double d);
  void setComboBoxChanged(int index);

 private:
  enum class Set { Mandelbrot, Julia };

  QGridLayout *m_grid;
  QLabel *m_imageLabel;
  int m_imageWidth = 800;
  int m_imageHeight = 800;
  double m_realNumber = 0.;
  double m_imgNumber = 0.;
  Set m_set;

  void setupGrid();
};

#endif  // WIDGET_H
