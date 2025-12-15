#include "ui/pomodoro-timer-widget.hpp"
#include "impl/pomodoro-calculator.hpp"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStringLiteral>
#include <QTranslator>
#include <QString>

void setStyleSheet(const QString &styleSheet)
{
	QFile file{styleSheet};

	if (not file.open(QFile::ReadOnly | QFile::ExistingOnly)) [[unlikely]]
	{
		qCritical() << "Failed to load stylesheet: " << styleSheet;
		return;
	}

	const auto ss{ QLatin1String{file.readAll()} };
	qInfo() << "QSS file was successfully opened";
	qApp->setStyleSheet(ss);

}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		impl::PomodoroCalculator calculator;
		qInfo() << calculator.calculate(QString{argv[1]}.toUShort());

		return 0;
	}

	QApplication paz(argc, argv);



	/*QTranslator translator;
	if (translator.load(QLocale(), "Paz"_L1, "-"_L1, ":i18n"_L1))
		QCoreApplication::installTranslator(&translator);*/
	setStyleSheet("../themes/default/style.qss");

	ui::PomodoroTimerWidget pomodoroTimerWidget;
	pomodoroTimerWidget.show();
	return QApplication::exec();
}