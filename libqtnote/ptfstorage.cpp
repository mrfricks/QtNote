/*
QtNote - Simple note-taking application
Copyright (C) 2010 Sergei Ilinykh

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Contacts:
E-Mail: rion4ik@gmail.com XMPP: rion@jabber.ru
*/

#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QSettings>
#include <QStyle>

#ifdef Q_OS_WIN
#include <QLibrary>
#include <shlobj.h>
#endif // Q_OS_WIN

#include "ptfdata.h"
#include "ptfstorage.h"
#include "utils.h"

namespace QtNote {

PTFStorage::PTFStorage(QObject *parent) : FileStorage(parent), icon(QLatin1String(":/icons/trayicon"))
{
    fileExt = "txt";
}

bool PTFStorage::init()
{
    auto path = QSettings().value("storage.ptf.path").toString();
    notesDir.setPath(path.isEmpty() ? findStorageDir() : path);
    if (!notesDir.isReadable() && !path.isEmpty()) {
        notesDir.setPath(findStorageDir()); // try default
    }
    if (!notesDir.exists()) {
        if (!notesDir.mkpath(QLatin1String("."))) {
            qWarning("can't create storage dir: %s", qPrintable(notesDir.absolutePath()));
        }
    }
    return isAccessible();
}

bool PTFStorage::isAccessible() const { return notesDir.isReadable(); }

const QString PTFStorage::systemName() const { return QLatin1String("ptf"); }

const QString PTFStorage::name() const { return tr("Plain Text Storage"); }

QIcon PTFStorage::storageIcon() const { return icon; }

QIcon PTFStorage::noteIcon() const { return icon; }

QList<NoteListItem> PTFStorage::noteListFromInfoList(const QFileInfoList &files)
{
    QList<NoteListItem> ret;
    foreach (const QFileInfo &fi, files) {
        PTFData note;
        if (note.fromFile(fi.canonicalFilePath())) {
            NoteListItem li(fi.completeBaseName(), systemName(), note.title(), note.dtLastChange);
            ret.append(li);
        }
    }
    return ret;
}

Note PTFStorage::note(const QString &noteId)
{
    if (!noteId.isEmpty()) {
        QString   fileName = QDir(notesDir).absoluteFilePath(QString("%1.%2").arg(noteId, fileExt));
        QFileInfo fi(fileName);
        if (fi.isWritable()) {
            PTFData *noteData = new PTFData;
            noteData->fromFile(fileName);
            return Note(noteData);
        }
        handleFSError();
    }
    return Note();
}

QString PTFStorage::saveNote(const QString &noteId, const QString &text)
{
    PTFData note;
    QString newNoteId = noteId;
    note.setText(text);
    if (!note.saveToFile(Utils::fileNameForText(notesDir, note.title(), fileExt, newNoteId))) {
        handleFSError();
        return QString();
    }
    if (!noteId.isEmpty() && noteId != newNoteId) {
        notesDir.remove(noteId + '.' + fileExt);
    }
    NoteListItem item(newNoteId, systemName(), note.title(), note.dtLastChange);
    putToCache(item, noteId); // noteId is old one. new one is in item.id
    return newNoteId;
}

bool PTFStorage::isRichTextAllowed() const { return false; }

QString PTFStorage::findStorageDir() const { return Utils::qtnoteDataDir() + QLatin1Char('/') + systemName(); }

} // namespace QtNote
