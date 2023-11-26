#include "widget.h"

#include <QColorDialog>
#include <QComboBox>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QtMath>
#include <complex>

Widget::Widget(QWidget *parent) : QWidget{parent} {
  setupGrid();
  this->setLayout(m_grid);
}

void Widget::CreateMdlbrotSet() {
  auto maxIter = 55;
  QImage im(QSize(m_imageWidth, m_imageHeight), QImage::Format_ARGB32);
  QColor pixel;

  for (int i = 0; i < m_imageWidth; ++i) {
    for (int j = 0; j < m_imageHeight; ++j) {
      std::complex<double> C(
          static_cast<double>(i) / m_imageWidth - m_realNumber,
          static_cast<double>(j) / m_imageHeight - m_imgNumber);
      std::complex<double> Z(0.f, 0.f);

      int iterations = 0;
      while (abs(Z) < 2.0 && iterations < maxIter) {
        Z = Z * Z + C;
        iterations++;
      }

      if (iterations < maxIter) {
        auto color = static_cast<double>(255 * iterations) / maxIter;
        pixel = QColor::fromRgb(color, 0, color);
      } else {
        pixel = QColor::fromRgb(0, 0, 0);
      }
      im.setPixelColor(i, j, pixel);
    }
  }
  m_imageLabel->setPixmap(QPixmap::fromImage(im));
}

void Widget::CreateJuliaSet() {
  auto maxIter = 55;
  auto iterations = 0;
  std::complex<double> C(m_realNumber, m_imgNumber);
  QImage im(QSize(m_imageWidth, m_imageHeight), QImage::Format_ARGB32);
  QColor pixel;
  for (int i = 0; i < m_imageWidth; ++i) {
    for (int j = 0; j < m_imageHeight; ++j) {
      std::complex<double> Z(static_cast<double>(i) / m_imageWidth - 1.5,
                             static_cast<double>(j) / m_imageHeight - 1.5);
      /*for (iterations = 0; iterations < maxIter; ++iterations) {
        if (abs(Z) < 2.0) {
          Z = Z * Z + C;
        } else {
          break;
        }
      }*/
      for (iterations = 0; iterations < maxIter; ++iterations) {
        if (abs(Z.imag()) < 50.) {
          Z = C * qSin(Z);
        } else {
          break;
        }
      }
      auto color = static_cast<double>(255 * iterations) / maxIter;
      pixel = QColor::fromRgb(color, 0, color);
      im.setPixelColor(i, j, pixel);
    }
  }
  m_imageLabel->setPixmap(QPixmap::fromImage(im));
}

void Widget::genImageButtonClicked() {
  if (m_set == Set::Mandelbrot) {
    CreateMdlbrotSet();
  } else if (m_set == Set::Julia) {
    CreateJuliaSet();
  }
}

void Widget::realSpinboxValueChanged(double d) { m_realNumber = d; }

void Widget::imgSpinboxValueChanged(double d) { m_imgNumber = d; }

void Widget::setComboBoxChanged(int index) {
  if (index == 0) {
    m_set = Set::Mandelbrot;
  } else if (index == 1) {
    m_set = Set::Julia;
  }
}

void Widget::colorButtonClicked() {
  m_pixelColor =
      QColorDialog::getColor(m_pixelColor, this, "Choose Text Color");
  qDebug() << m_pixelColor;
}

void Widget::setupGrid() {
  m_grid = new QGridLayout(this);
  m_imageLabel = new QLabel(this);
  QImage im(QSize(m_imageWidth, m_imageHeight), QImage::Format_ARGB32);
  m_imageLabel->setPixmap(QPixmap::fromImage(im));

  QHBoxLayout *realBox = new QHBoxLayout(this);
  QLabel *realLabel = new QLabel(this);
  realLabel->setText(tr("Real Number:"));
  QDoubleSpinBox *realNumber = new QDoubleSpinBox(this);
  realNumber->setRange(-10., 10.);
  realNumber->setDecimals(3);
  realBox->addWidget(realLabel);
  realBox->addWidget(realNumber);

  QObject::connect(realNumber, &QDoubleSpinBox::valueChanged, this,
                   &Widget::realSpinboxValueChanged);

  QHBoxLayout *imgBox = new QHBoxLayout(this);
  QLabel *imgLabel = new QLabel(this);
  imgLabel->setText(tr("Img. Number:"));
  QDoubleSpinBox *imgNumber = new QDoubleSpinBox(this);
  imgNumber->setRange(-10., 10.);
  imgNumber->setDecimals(3);
  imgBox->addWidget(imgLabel);
  imgBox->addWidget(imgNumber);

  QObject::connect(imgNumber, &QDoubleSpinBox::valueChanged, this,
                   &Widget::imgSpinboxValueChanged);

  QPushButton *genButton = new QPushButton("Generate Image", this);
  QObject::connect(genButton, &QPushButton::clicked, this,
                   &Widget::genImageButtonClicked);

  QComboBox *cbox = new QComboBox(this);
  cbox->addItem("Mandelbrot Set");
  cbox->addItem("Julia Set");
  m_set = static_cast<Set>(cbox->currentIndex());
  QObject::connect(cbox, &QComboBox::activated, this,
                   &Widget::setComboBoxChanged);

  QPushButton *colorButton = new QPushButton("Change Color", this);
  QObject::connect(colorButton, &QPushButton::clicked, this,
                   &Widget::colorButtonClicked);

  m_grid->addWidget(m_imageLabel, 0, 0, 1, 2);
  m_grid->addItem(realBox, 1, 0, 1, 1);
  m_grid->addItem(imgBox, 2, 0, 1, 1);
  m_grid->addWidget(genButton, 1, 1, 1, 1);
  m_grid->addWidget(cbox, 2, 1, 1, 1);
  m_grid->addWidget(colorButton, 3, 1, 1, 1);
  m_grid->setAlignment(Qt::AlignCenter);
}
