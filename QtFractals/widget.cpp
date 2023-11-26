#include "widget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <complex>

Widget::Widget(QWidget *parent, int imWidth, int imHeight)
    : QWidget{parent}, m_imageWidth{imWidth}, m_imageHeight{imHeight} {
  setParent(parent);

  m_grid = new QGridLayout(this);
  m_imageLabel = new QLabel(this);
  QImage im(QSize(m_imageWidth, m_imageHeight), QImage::Format_ARGB32);
  m_imageLabel->setPixmap(QPixmap::fromImage(im));

  QHBoxLayout *realBox = new QHBoxLayout(this);
  QLabel *realLabel = new QLabel(this);
  realLabel->setText(tr("Real Number:"));
  QSpinBox *realNumber = new QSpinBox(this);
  realBox->addWidget(realLabel);
  realBox->addWidget(realNumber);

  QHBoxLayout *imgBox = new QHBoxLayout(this);
  QLabel *imgLabel = new QLabel(this);
  imgLabel->setText(tr("Img. Number:"));
  QSpinBox *imgNumber = new QSpinBox(this);
  imgBox->addWidget(imgLabel);
  imgBox->addWidget(imgNumber);

  QPushButton *genButton = new QPushButton("Generate Image", this);

  m_grid->addWidget(m_imageLabel, 0, 0, 1, 2);
  m_grid->addItem(realBox, 1, 0, 1, 1);
  m_grid->addItem(imgBox, 2, 0, 1, 1);
  m_grid->addWidget(genButton, 1, 1, 2, 1);
  m_grid->setAlignment(Qt::AlignCenter);
  this->setLayout(m_grid);

  QObject::connect(genButton, &QPushButton::clicked, this,
                   &Widget::buttonClicked);
}

void Widget::updateImageData() {
  auto maxColor = 255;
  auto maxIter = 55;
  QImage im(QSize(m_imageWidth, m_imageHeight), QImage::Format_ARGB32);
  QColor pixel;
  for (int i = 0; i < m_imageWidth; ++i) {
    for (int j = 0; j < m_imageHeight; ++j) {
      std::complex<float> C(static_cast<float>(i) / m_imageWidth - 1.5f,
                            static_cast<float>(j) / m_imageHeight - 0.5f);
      std::complex<float> Z(0.f, 0.f);
      int iterations = 0;
      while (abs(Z) < 2.0 && iterations < maxIter) {
        Z = Z * Z + C;
        iterations++;
      }
      if (iterations < maxIter) {
        int color = int(maxColor * iterations / maxIter);
        pixel = QColor::fromRgb(color, 0, 0);
      } else {
        pixel = QColor::fromRgb(0, 0, 0);
      }
      im.setPixelColor(i, j, pixel);
    }
  }
  m_imageLabel->setPixmap(QPixmap::fromImage(im));
}

void Widget::buttonClicked() { updateImageData(); }
