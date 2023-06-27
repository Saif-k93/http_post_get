

#include <QCoreApplication>
#include "worker.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker;

    worker.get("https://postman-echo.com/get?foo1=bar1&foo2=bar2");

    QByteArray data =
        {
            "param1=hello"
            "&"
            "param2=foo"
        };

    worker.post("https://postman-echo.com/post",data);



    return a.exec();
}
