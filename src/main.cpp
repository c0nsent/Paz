#include "ui/main-window.hpp"

#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	paz::ui::MainWindow mainWindow;
	mainWindow.show();

	return QApplication::exec();
}