// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

MemoryChunk::MemoryChunk(qint32 size) {
    data = static_cast<quint8*>(malloc(static_cast<size_t>(size)));
    next = nullptr;
}

MemoryChunk::~MemoryChunk() {
    free(data);
}
