#include "widget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>

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
  auto max_color = 255;
  QImage im(QSize(m_imageWidth, m_imageHeight), QImage::Format_ARGB32);
  for (int i = 0; i < m_imageWidth; ++i) {
    for (int j = 0; j < m_imageHeight; ++j) {
      auto r =
          max_color * static_cast<float>(i) / static_cast<float>(m_imageWidth);
      auto g =
          max_color * static_cast<float>(j) / static_cast<float>(m_imageHeight);
      auto b =
          max_color * static_cast<float>(j) / static_cast<float>(m_imageHeight);
      QColor pixel = QColor::fromRgb(r, g, b);
      im.setPixelColor(i, j, pixel);
    }
  }
  m_imageLabel->setPixmap(QPixmap::fromImage(im));
}

void Widget::buttonClicked() { updateImageData(); }
