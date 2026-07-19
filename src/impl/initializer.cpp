#include "initializer.hpp"


namespace impl
{
    Initializer::Initializer(QGuiApplication *app) : QObject{app}
    {
        m_settingsManager = findChild<SettingsManager *>(Qt::FindDirectChildrenOnly);

        if (m_settingsManager == nullptr)
            m_settingsManager = new SettingsManager{app};
    }

    auto Initializer::createPomodoroTimer() -> PomodoroTimer *
    {
        const auto pt{new(std::nothrow) PomodoroTimer{this->parent(), m_settingsManager->getInfoForPomodoroTimer()}};

        if (pt == nullptr) return pt;

        m_settingsManager->setupConnections(pt);

        connect(reinterpret_cast<QGuiApplication *>(this->parent()),
            &QGuiApplication::aboutToQuit,
            m_settingsManager,
            &SettingsManager::sync
        );

        return pt;
    }

    auto Initializer::createPomodoroStats() -> PomodoroStats *
    {
        return new(std::nothrow) PomodoroStats{this->parent()};
    }


    auto Initializer::createSystemTrayIcon() -> QSystemTrayIcon *
    {
        auto systemTray{new(std::nothrow) QSystemTrayIcon{this->parent()}};

        if (systemTray == nullptr) return systemTray;

        connect(this->parent()->findChild<PomodoroTimer *>(Qt::FindDirectChildrenOnly),
            &PomodoroTimer::timerFinished,
            [&systemTray] (const PomodoroTimer::Phase currentPhase)
            {
                const QString message{ currentPhase == PomodoroTimer::Phase::Work ?
                    tr("It is time to be productive") : tr("You can chill a bit")};
                systemTray->showMessage(tr("Time is out"), message, QSystemTrayIcon::NoIcon);
            }
        );
        
        return systemTray;
    }
}
