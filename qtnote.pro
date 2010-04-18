# -------------------------------------------------
# Project created by QtCreator 2009-02-10T13:06:32
#
# QtNote - Simple note-taking application
# Copyright (C) 2010 Ili'nykh Sergey
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Contacts:
# E-Mail: rion4ik@gmail.com XMPP: rion@jabber.ru
# -------------------------------------------------

TARGET = qtnote
TEMPLATE = app
SOURCES += main.cpp \
    mainwidget.cpp \
    tomboynote.cpp \
    notedialog.cpp \
    note.cpp \
    notemanager.cpp \
    notestorage.cpp \
    tomboystorage.cpp \
    qtnoteptfstorage.cpp
HEADERS += mainwidget.h \
    tomboynote.h \
    notedialog.h \
    note.h \
    notemanager.h \
    notestorage.h \
    tomboystorage.h \
    qtnoteptfstorage.h
RESOURCES += main.qrc
QT += xml
FORMS += notedialog.ui
unix { 
    target.path = $$PREFIX/usr/bin
    INSTALLS += target
}
