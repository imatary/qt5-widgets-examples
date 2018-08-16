#include "mainform.h"
#include <QApplication>
#include <QFile>
#include <QtPlugin>

#if defined(Q_OS_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif




Q_IMPORT_PLUGIN(QICOPlugin)
//Q_IMPORT_PLUGIN(QJpegPlugin)
//Q_IMPORT_PLUGIN(QGifPlugin)
//Q_IMPORT_PLUGIN(QTgaPlugin)
//Q_IMPORT_PLUGIN(QSvgPlugin)
Q_IMPORT_PLUGIN(QSvgIconPlugin)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QFile styleFile("styles/default.qss");  

    styleFile.open(QFile::ReadOnly);
    // Apply the loaded stylesheet
    QString style(styleFile.readAll());
    a.setStyleSheet(style);
    


    MainForm w;
    w.show();

    return a.exec();
}
