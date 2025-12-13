/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-widget.hpp"

#include <QString>
#include <QtMinMax>

namespace ui
{
	void PomodoroTimerWidget::setupWidget()
	{
		m_font.setPointSize(20);

		updatePhaseLabelText(m_timer->phase());
		updateRemainingTimeText(m_timer->phaseDuration());
		updatePhaseProgress();
		m_phaseProgress->setTextVisible(false);
		updatePomodoroCountText();

		updateStartPauseButtonText(m_timer->state());
		m_resetButton->setText(tr("Reset"));
		m_skipBreakButton->setText(tr("Skip Break"));
		updateSkipBreakButtonVisibility(m_timer->phase());

		const auto labels{this->findChildren<QLabel *>()};
		for (const auto label : labels)
		{
			label->setAlignment(Qt::AlignCenter);
			label->setFont(m_font);
		}

		const auto buttons{this->findChildren<QPushButton *>()};
		for (const auto button : buttons)
		{
			button->setFont(m_font);
		}

		m_mainLayout->addWidget(m_phaseLabel);
		m_mainLayout->addWidget(m_remainingTimeLabel);
		m_mainLayout->addWidget(m_phaseProgress);
		m_mainLayout->addWidget(m_completedPomodorosLabel);
		m_mainLayout->addWidget(m_startPauseButton);
		m_mainLayout->addWidget(m_resetButton);
		m_mainLayout->addWidget(m_skipBreakButton);

		m_mainLayout->setAlignment(Qt::AlignCenter);
		m_mainLayout->setContentsMargins(24, 24, 24, 24);
		m_mainLayout->setSpacing(16);

		m_mainLayout->setObjectName("mainLayout");
		m_phaseLabel->setObjectName("phaseLabel");
		m_remainingTimeLabel->setObjectName("remainingTimeLabel");
		m_phaseProgress->setObjectName("phaseProgress");
		m_completedPomodorosLabel->setObjectName("completedPomodoroLabel");
		m_startPauseButton->setObjectName("startPauseButton");
		m_resetButton->setObjectName("resetButton");
		m_skipBreakButton->setObjectName("skipBreakButton");

	}


	void PomodoroTimerWidget::setupConnections()
	{
		connect(
			m_timer,
			&impl::PomodoroTimer::phaseChanged,
			this,
			&PomodoroTimerWidget::updatePhaseLabelText
		);

		connect(
			m_timer,
			&impl::PomodoroTimer::remainingTimeChanged,
			this,
			&PomodoroTimerWidget::updateRemainingTimeText
		);


		connect(
			m_timer,
			&impl::PomodoroTimer::remainingTimeChanged,
			m_phaseProgress,
			&QProgressBar::setValue
		);
		connect(
			m_timer,
			&impl::PomodoroTimer::phaseChanged,
			this,
			&PomodoroTimerWidget::updatePhaseProgress
		);

		connect(
			m_timer,
			&impl::PomodoroTimer::pomodoroFinished,
			this,
			&PomodoroTimerWidget::updatePomodoroCountText
		);

		connect(m_timer,
			&impl::PomodoroTimer::stateChanged,
			this,
			&PomodoroTimerWidget::updateStartPauseButtonText
		);

		connect(m_startPauseButton, &QPushButton::clicked, [this]
		{
			m_timer->state() == impl::PomodoroTimer::State::Idle ? m_timer->start() : m_timer->pause();
		});

		connect(m_resetButton, &QPushButton::clicked, m_timer, &impl::PomodoroTimer::reset);

		connect(m_skipBreakButton, &QPushButton::clicked, m_timer, &impl::PomodoroTimer::toNextPhase);
		connect(
			m_timer,
			&impl::PomodoroTimer::phaseChanged,
			this,
			&PomodoroTimerWidget::updateSkipBreakButtonVisibility
		);
	}


	void PomodoroTimerWidget::readSettings()
	{
		m_settings->beginGroup(settings::groups::c_pomodoroTimer);

		auto validate = [&](const QString &key, const quint16 defaultDuration)
		{
			const quint16 configValue{static_cast<quint16>(m_settings->value(key).toUInt())};

			if (limits::c_minPhaseDuration < configValue and configValue > limits::c_maxPhaseDuration)
				return configValue;

			return defaultDuration;
		};

		m_timer->setPhaseDuration(
			validate(settings::keys::c_workDuration, defaults::c_workDuration),
			validate(settings::keys::c_shortBreakDuration, defaults::c_shortBreakDuration),
			validate(settings::keys::c_longBreakDuration, defaults::c_longBreakDuration)
		);

		auto sessionLength{static_cast<quint16>(m_settings->value(settings::keys::c_sessionLength).toUInt())};

		if (limits::c_minSessionLength > sessionLength or sessionLength < limits::c_maxSessionLength)
			sessionLength = defaults::c_sessionLength;

		m_timer->setSessionLength(sessionLength);

		m_settings->endGroup();

		m_settings->beginGroup(settings::groups::c_style);

		m_font.setFamily(m_settings->value(settings::keys::c_fontFamily).toString());
		if (not m_font.exactMatch()) m_font.setFamily(defaults::c_fontFamily);

		m_settings->endGroup();
	}


	void PomodoroTimerWidget::writeSettings()
	{
		using enum impl::PomodoroTimer::Phase;
		m_settings->beginGroup(settings::groups::c_pomodoroTimer);

		auto writeValue = [&](const QString &key, const quint16 current)
		{
			if (not m_settings->contains(key)) m_settings->setValue(key, current);
		};

		writeValue(settings::keys::c_workDuration, m_timer->phaseDuration(Work));
		writeValue(settings::keys::c_shortBreakDuration, m_timer->phaseDuration(ShortBreak));
		writeValue(settings::keys::c_longBreakDuration, m_timer->phaseDuration(LongBreak));
		writeValue(settings::keys::c_sessionLength, m_timer->sessionLength());

		m_settings->endGroup();

		m_settings->beginGroup(settings::groups::c_style);
		m_settings->setValue(settings::keys::c_fontFamily, m_font.family());
		m_settings->endGroup();
	}


	PomodoroTimerWidget::PomodoroTimerWidget(QWidget *parent) : QWidget{parent}
	{
		setObjectName("PomodoroTimerWidget");
	    setLayout(m_mainLayout);
        setFont(m_font);

        setupWidget();
        setupConnections();

        readSettings();
        writeSettings();

		m_timer->setPhaseDuration(3, 3, 3);
	}


	void PomodoroTimerWidget::updatePhaseLabelText(const impl::PomodoroTimer::Phase current)
	{
		m_phaseLabel->setText(c_phaseStrings[qToUnderlying(current)]);
	}


	void PomodoroTimerWidget::updateStartPauseButtonText(const impl::PomodoroTimer::State current)
	{
		m_startPauseButton->setText(c_timerStateStrings[qToUnderlying(current)]);
	}


	void PomodoroTimerWidget::updateRemainingTimeText(const quint16 current)
	{
		const auto minutes {current / 60};
		const auto seconds {current % 60};

		m_remainingTimeLabel->setText(QString::asprintf("%d:%02d", minutes, seconds));
	}


	void PomodoroTimerWidget::updatePhaseProgress()
	{
		const auto currentPhaseDuration{m_timer->phaseDuration()};

		m_phaseProgress->setMaximum(currentPhaseDuration);
		m_phaseProgress->setValue(currentPhaseDuration);
	}


	void PomodoroTimerWidget::updatePomodoroCountText()
	{
		const auto suffix{m_completedPomodoros > 1 ? QChar{'s'} : QChar{}};

		m_completedPomodorosLabel->setText(QStringLiteral("%1 pomodoro%2")
			.arg(QString::number(m_completedPomodoros++), suffix));

		//m_completedPomodorosLabel->setText(tr("%n pomodoro(s)", nullptr, m_completedPomodoros++));
	}


	void PomodoroTimerWidget::updateSkipBreakButtonVisibility(const impl::PomodoroTimer::Phase current)
	{
		m_skipBreakButton->setHidden(current == impl::PomodoroTimer::Phase::Work);
	}
}
