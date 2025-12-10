#include "ui/pomodoro-timer-widget.hpp"

#include <QApplication>
#include <QTranslator>
#include <QStringLiteral>
#include <QStyle>
#include <QFile>

int main(int argc, char *argv[])
{
	using namespace Qt::StringLiterals;
	using namespace Qt::Literals;

	QApplication paz(argc, argv);

	/*QTranslator translator;
	if (translator.load(QLocale(), "Paz"_L1, "-"_L1, ":i18n"_L1))
		QCoreApplication::installTranslator(&translator);*/

	QFile file("../themes/default/style.qss");
	if(file.open(QFile::ReadOnly)) {
		QString StyleSheet = QLatin1String(file.readAll());
		qApp->setStyleSheet(StyleSheet);
	}
	else
		qInfo() << "БЛЯДЬ";
	ui::PomodoroTimerWidget pomodoroTimerWidget;
	pomodoroTimerWidget.show();
	//QApplication::setStyle("Macintosh");
	//paz.setStyleSheet("QPushButton { color: red }");
	return QApplication::exec();
}