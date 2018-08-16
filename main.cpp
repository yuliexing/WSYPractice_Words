#include "mainwindow.h"
#include <QApplication>

#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (argc > 1)
    {
        QString arg = QString(argv[1]);
        if (arg == "-h" || arg == "/h" || arg == "-help")
        {
            printf("%s [filename]\n", a.applicationName().toStdString().c_str());
            return 0;
        }
        if (arg == "-a")
        {
            w.setIsAutoInput(true);
        }
        else if (arg == "-o")
        {
            w.setSourceFile("");
        }
        else 
        {
            w.setSourceFile(arg);
        }
    }
    w.show();

    return a.exec();
    
}
