#include "mainwindow.h"
#include "infowindow.h"
#include "common.h"

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("CFO");
    QCoreApplication::setOrganizationDomain("CFO.com");
    QCoreApplication::setApplicationName("Elastic band");

    QScreen *screen = QGuiApplication::screens()[0];
    qreal dotsPerInchX = screen->physicalDotsPerInchX();
    qreal dotsPerInchY = screen->physicalDotsPerInchY();
    qreal dotsPerInch = qMin(dotsPerInchX, dotsPerInchY);
    qDebug() << "dpi:" << dotsPerInch << " dpiX:" << dotsPerInchX << " dpiY:" << dotsPerInchY;
    DOTS_PER_MM = dotsPerInch / 25.39999918;
    qDebug() << "DOTS_PER_MM:" << DOTS_PER_MM << " dpi:" << dotsPerInch;

    infoWindow w1;

    QFile qssFile(":/res/style.qss");
    if (qssFile.open(QFile::ReadOnly))
    {
        a.setStyleSheet(qssFile.readAll());
    }
    qssFile.close();

    w1.setWindowTitle("CFO-20240908");
    w1.setWindowFlags(Qt::FramelessWindowHint);

    // 获取屏幕指针列表
    QList<QScreen *> screenList = QGuiApplication::screens();
    QRect rect = screenList[2]->geometry();  // 若有多个屏幕，可选择不同的下标0,1,2......
    qDebug() << "rect=" << rect;
    w1.setGeometry(rect);


    w1.show();
//    w1.showMaximized();





    return a.exec();
}
