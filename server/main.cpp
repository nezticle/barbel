#include <QtCore/QCoreApplication>

#include <Barbel/servermanager.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("Bsquask");
    app.setOrganizationDomain("bsquask.com");
    app.setApplicationName("BarbelServer");

    Barbel::ServerManager server;
    server.listen(QHostAddress("127.0.0.1"), 54540);

    return app.exec();
}

