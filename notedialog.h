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

#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class NoteDialog;
}

class NoteDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(NoteDialog)
public:
	explicit NoteDialog(QWidget *parent, const QString &storageId, const QString &noteId);
    virtual ~NoteDialog();
	void setText(QString text);
	QString text();
	bool checkOwnership(const QString &storageId, const QString &noteId) const;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::NoteDialog *m_ui;
	QString storageId_;
	QString noteId_;
	bool trashRequested_;
	bool modified_;

signals:
	void trashRequested(const QString &, const QString &);
	void saveRequested(const QString &, const QString &, const QString &);

public slots:
	void done(int r);

private slots:
	void trashClicked();
};

#endif // NOTEDIALOG_H
