#include "QtIrbis.h"

//=========================================================

const char IrbisText::CrLf[] = { 0x0D, 0x0A };
const char IrbisText::Lf[] = { 0x0A };

// Разделитель строк в ИРБИС.
const QString IrbisText::IrbisDelimiter = "\u001F\u001E";

// Короткая версия разделителя строк.
const QString IrbisText::ShortDelimiter = "\u001E";

// Разделитель строк в MSDOS
const QString IrbisText::MsDosDelimiter = "\r\n";

// Разделитель строк в UNIX.
const QString IrbisText::UnixDelimiter = "\n";

const QString IrbisText::SearchDelimiter = "#";

// Замена разделителей текста с ИРБИС на MS-DOS.

QString IrbisText::fromIrbisToDos (QString &text) {
    return text.replace(IrbisDelimiter, MsDosDelimiter);
}

// Замена разделителей текста с MS-DOS на ИРБИС.
QString IrbisText::fromDosToIrbis (QString &text) {
    return text.replace(MsDosDelimiter, IrbisDelimiter);
}

// Замена разделителей текста с MS-DOS на UNIX.
QString IrbisText::fromDosToUnix(QString &text) {
    return text.replace(MsDosDelimiter, UnixDelimiter);
}

// Разбивка ответа сервера по строкам (полный вариант разделителя).
QStringList IrbisText::fromFullDelimiter (const QString &text) {
    return text.split(IrbisDelimiter);
}

// Строки, приходящие в ответ на команду WriteRecord.
QStringList IrbisText::fromShortDelimiter(const QString &text) {
    return text.split(ShortDelimiter);
}

// Считываем весь файл как строку в кодировке ANSI
QString IrbisText::readAllAnsi(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }

    QByteArray bytes = file.readAll();
    QString result = IrbisEncoding::ansi()->toUnicode(bytes);

    return result;
}

// Считываем весь файл как строку в кодировке UTF-8
QString IrbisText::readAllUtf(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }

    QByteArray bytes = file.readAll();
    QString result = IrbisEncoding::ansi()->toUnicode(bytes);

    return result;
}

// Считываем весь файл как массив строк в кодировке ANSI
QStringList IrbisText::readAnsiLines(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw new IrbisException();
    }

    QStringList result;
    QTextCodec *ansi = IrbisEncoding::ansi();
    while (true) {
        QByteArray bytes = file.readLine();
        if (bytes.isEmpty()) {
            break;
        }

        QString line = ansi->toUnicode(bytes);
        result.append(line);
    }

    return result;
}

// Считываем весь файл как массив строк в кодировке UTF-8
QStringList IrbisText::readUtfLines(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw new IrbisException();
    }

    QStringList result;
    QTextCodec *utf = IrbisEncoding::utf();
    while (true) {
        QByteArray bytes = file.readLine();
        if (bytes.isEmpty()) {
            break;
        }

        QString line = utf->toUnicode(bytes);
        result.append(line);
    }

    return result;
}
