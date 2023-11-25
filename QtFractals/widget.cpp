#include "widget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>

Widget::Widget(QWidget *parent) : QWidget{parent} {
  setParent(parent);

  m_grid = new QGridLayout(this);
  m_imageLabel = new QLabel(this);

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
  updateImageData();
}

void Widget::updateImageData() {
  auto width = 500;
  auto height = 500;
  auto max_color = 255;
  QImage im(QSize(width, height), QImage::Format_ARGB32);
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      auto r = max_color * static_cast<float>(i) / static_cast<float>(width);
      auto g = max_color * static_cast<float>(j) / static_cast<float>(height);
      auto b = max_color * static_cast<float>(j) / static_cast<float>(height);
      QColor pixel = QColor::fromRgb(r, g, b);
      im.setPixelColor(i, j, pixel);
    }
  }
  QPixmap pm = QPixmap::fromImage(im);
  m_imageLabel->setPixmap(pm);
}
