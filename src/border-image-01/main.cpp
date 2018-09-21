﻿#include "widget.h"
#include "widget01.h"
#include "widget02.h"
#include "widget03.h"
#include "widget04.h"
#include <QApplication>
#include <QFile>
#include <QtPlugin>
#include <QStandardPaths>
#include <QDebug>

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#endif

#if defined(Q_OS_WIN32)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
      
    //Q_IMPORT_PLUGIN(QSQLiteDriverPlugin)
    Q_IMPORT_PLUGIN(QICOPlugin)
    //Q_IMPORT_PLUGIN(QJpegPlugin)
    //Q_IMPORT_PLUGIN(QGifPlugin)
    //Q_IMPORT_PLUGIN(QTgaPlugin)
    Q_IMPORT_PLUGIN(QSvgPlugin)
    Q_IMPORT_PLUGIN(QSvgIconPlugin)
#elif defined(Q_OS_MAC)
    Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif

int main(int argc, char *argv[])
{
#ifdef WIN32
        // detach from the current console window
        // if launched from a console window, that will still run waiting for the new console (below) to close
        // it is useful to detach from Qt Creator's <Application output> panel
        FreeConsole();
        // create a separate new console window
        AllocConsole();
        // attach the new console to this application's process
        AttachConsole(GetCurrentProcessId());
        SetConsoleOutputCP(65001);
        // reopen the std I/O streams to redirect I/O to the new console
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
        freopen("CON", "r", stdin);
#endif

    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    QFile qss(":/qss/assets/styles/style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();


    /* Widget window;
     window.show();*/

    //Widget01 widget01;
    //widget01.show();

    //Widget02 widget02;
    //widget02.show();

    //Widget03 widget03;
    //widget03.show();

    Widget04 widget04;
    widget04.show();


    qDebug() << QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    qDebug() << QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    

    qDebug() << QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    qDebug() << QStandardPaths::standardLocations(QStandardPaths::DataLocation);


    qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);

    qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    qDebug() << QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);



    return a.exec();
}