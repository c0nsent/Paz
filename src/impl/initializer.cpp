#include "initializer.hpp"



namespace impl
{
    Initializer::Initializer(QGuiApplication *app) : QObject{app} {}

    auto Initializer::createPomodoroTimer() -> PomodoroTimer *
    {
        const auto pt{ new PomodoroTimer{this->parent(), m_settingsManager.getInfoForPomodoroTimer()} };
        m_settingsManager.setupConnections(pt);

        return pt;
    }

    auto Initializer::createPomodoroStats() -> PomodoroStats * {}

}