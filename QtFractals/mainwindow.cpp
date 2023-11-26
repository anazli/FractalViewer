#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_widget = new Widget(this);
  setCentralWidget(m_widget);
  m_widget->setSizePolicy(QSizePolicy::Policy::Expanding,
                          QSizePolicy::Policy::Expanding);
}

MainWindow::~MainWindow() {}
