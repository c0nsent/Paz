#include <QtWidgets>
#include "backend/pomodoro-timer-backend.hpp"

int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	QWidget window{};
	window.resize(800, 600);
	window.show();
	window.setWindowTitle( "Paz" );
	return QApplication::exec();
}