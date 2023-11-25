#include <QApplication>
#include <QScreen>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  int width = 800;
  int height = 800;

  QScreen *screen = a.primaryScreen();
  int screenWidth = screen->geometry().width();
  int screenHeight = screen->geometry().height();

  MainWindow w;
  w.setGeometry((screenWidth - width) / 2.0, (screenHeight - height) / 2.0,
                width, height);
  w.show();
  return a.exec();
}
