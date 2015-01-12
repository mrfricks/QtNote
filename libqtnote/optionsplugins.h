#ifndef OPTIONSPLUGINS_H
#define OPTIONSPLUGINS_H

#include <QWidget>

namespace Ui {
class OptionsPlugins;
}

namespace QtNote {

class Main;
class PluginsModel;

class OptionsPlugins : public QWidget
{
	Q_OBJECT

public:
	explicit OptionsPlugins(Main *qtnote, QWidget *parent = 0);
	~OptionsPlugins();

private:
	Ui::OptionsPlugins *ui;
	Main *qtnote;
	PluginsModel *pluginsModel;
};

} // namespace QtNote

#endif // OPTIONSPLUGINS_H
