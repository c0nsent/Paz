#include <QtWidgets>
//#include "backend/pomodoro-timer-backend.hpp"
#include "backend/pomodor-timer/timer-phase.hpp"
#include <QDebug>

int main(int argc, char *argv[])
{
	/*QApplication app{argc, argv};
	QWidget window{};
	window.resize(800, 600);
	window.show();
	window.setWindowTitle( "Paz" );
	return QApplication::exec();*/
	const paz::backend::TimerPhase *const phase = new paz::backend::TimerPhase(paz::backend::TimerPhase::Phase::work);


	qInfo() << phase->getPhase();
}