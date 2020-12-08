/*
QtNote - Simple note-taking application
Copyright (C) 2010 Ili'nykh Sergey

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

#include <QColor>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>

#include "utils.h"

Utils::Utils() { }

QString Utils::cuttedDots(const QString &src, int length)
{
    Q_ASSERT(length > 3);
    if (src.length() > length) {
        return src.left(length - 3) + "...";
    }
    return src;
}

const QString Utils::genericDataDir() { return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation); }

const QString &Utils::qtnoteDataDir()
{
    static QString dataDir;
    if (dataDir.isEmpty()) {
        QSettings s;
        dataDir = genericDataDir() + QLatin1Char('/') + s.organizationName() + QLatin1Char('/') + s.applicationName();
    }
    return dataDir;
}

QColor Utils::perceptiveColor(const QColor &against)
{
    float brightness = (0.299 * against.redF() + 0.587 * against.greenF() + 0.114 * against.blueF());
    if (brightness >= 0.5) {
        return QColor(Qt::black);
    }
    return QColor(Qt::white);
}

QColor Utils::mergeColors(const QColor &a, const QColor &b)
{
    qreal alphaA(a.alphaF());
    qreal alphaB(b.alphaF());
    return QColor::fromRgbF((a.redF() * alphaA) + (b.redF() * alphaB * (1 - alphaA)),
                            (a.greenF() * alphaA) + (b.greenF() * alphaB * (1 - alphaA)),
                            (a.blueF() * alphaA) + (b.blueF() * alphaB * (1 - alphaA)),
                            alphaA + (alphaB * (1 - alphaA)));
}
