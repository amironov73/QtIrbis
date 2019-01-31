#include <QtCore>

#include "QtIrbis.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream cout(stdout, QIODevice::WriteOnly);

    try {
        IrbisConnection connection;
        connection.host = "127.0.0.1";
        connection.port = 6666;
        connection.username = "1";
        connection.password = "1";
        connection.database = "IBIS";
        connection.workstation = 'C';

        connection.connect();
        qint32 maxMfn = connection.getMaxMfn("IBIS");
        cout << maxMfn << endl;

        QList<qint32> found = connection.search("K=АЛГЕБР$");
        for (qint32 mfn : found) { cout << ' ' << mfn; }
        cout << endl;

        FileSpecification specification(IrbisPath::MasterFile, "IBIS", "NJGAZ.WSS");
        QString text = connection.readTextFile(specification);
        cout << text << endl;

    } catch (QException ex) {
        cout << QString(ex.what()) << endl;
    }
}
