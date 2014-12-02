#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

namespace Ui {
class NoteWidget;
}

class TypeAheadFindBar;

namespace QtNote {

class NoteWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit NoteWidget(const QString &storageId, const QString &noteId);
	~NoteWidget();

	static void initActions();

	void setText(QString text);
	QString text();
	void setAcceptRichText(bool state);
	inline QString storageId() const { return _storageId; }
	inline QString noteId() const { return noteId_; }
	void setNoteId(const QString &noteId);
	inline const QString &firstLine() const { return _firstLine; }
	inline qint64 lastChangeElapsed() const { return _lastChangeElapsed.elapsed(); }

signals:
	void firstLineChanged();
	void trashRequested();
	void saveRequested();
	void noteIdChanged(const QString &oldId, const QString &newId);
	void invalidated(); // emited when we are unsure we have the latest data

protected:
	void changeEvent(QEvent *e);
	void keyPressEvent(QKeyEvent *event);	
public slots:
	void save();
private slots:
	void autosave();
	void onCopyClicked();
	void textChanged();
	void onPrintClicked();
	void onSaveClicked();
	void onTrashClicked();

private:
	Ui::NoteWidget *ui;

	TypeAheadFindBar *findBar;
	QString _storageId;
	QString noteId_;
	QString _firstLine;
	QString extFileName_;
	QTimer _autosaveTimer;
	QElapsedTimer _lastChangeElapsed;
	bool _trashRequested;
	bool _changed;

	static QHash<QString,QAction*> _actions;

	QAction *cloneAction(const QString &name);
};

} // namespace QtNote

#endif // NOTEWIDGET_H
