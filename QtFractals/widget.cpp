#include "widget.h"

#include <QSpinBox>

Widget::Widget(QWidget *parent) : QWidget{parent} {
  setParent(parent);

  m_grid = new QGridLayout(this);

  QLabel *realLabel = new QLabel(this);
  realLabel->setText(tr("Real Number"));
  QLabel *imaginLabel = new QLabel(this);
  imaginLabel->setText(tr("Imaginary Number"));
  m_imageLabel = new QLabel(this);
  m_imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QSpinBox *realNumber = new QSpinBox(this);
  QSpinBox *imgNumber = new QSpinBox(this);

  m_grid->addWidget(realLabel, 0, 0, 1, 1);
  m_grid->addWidget(realNumber, 1, 0, 1, 1);
  m_grid->addWidget(imaginLabel, 2, 0, 1, 1);
  m_grid->addWidget(imgNumber, 3, 0, 1, 1);
  m_grid->addWidget(m_imageLabel, 0, 1, 4, 1);
  m_grid->setAlignment(Qt::AlignTop);
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
