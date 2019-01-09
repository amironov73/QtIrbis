#include "QtIrbis.h"

//=========================================================

ServerResponse::ServerResponse(QTcpSocket *socket) {
    this->socket = socket;
    // TODO implement
}

void ServerResponse::close() {
    socket->close();
}
