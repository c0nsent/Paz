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

		for (const auto label : findChildren<QLabel *>())
		{
			label->setAlignment(Qt::AlignCenter);
			label->setFont(m_font);
		}

		for (const auto button : findChildren<QPushButton *>())
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
		m_settings->beginGroup(settings::groups::POMODORO_TIMER);

		auto toQuint16 = [&](const QAnyStringView key)
		{
			return static_cast<quint16>(m_settings->value(key).toUInt());
		};

		for (auto i{0}; i != phaseMeta.keyCount(); ++i)
		{
			const auto configValue{ toQuint16(settings::keys::PHASE_DURATIONS.at(i)) };

			const quint16 clamped{ qBound(limits::MIN_PHASE_DURATION, configValue, limits::MAX_PHASE_DURATION) };

			m_timer->setPhaseDuration(static_cast<impl::PomodoroTimer::Phase>(i), clamped);
		}

		const auto sessionLength{ toQuint16(settings::keys::SESSION_LENGTH) };

		m_timer->setSessionLength(qBound(limits::MIN_SESSION_LENGTH, sessionLength, limits::MAX_SESSION_LENGTH));

		m_settings->endGroup();

		m_settings->beginGroup(settings::groups::STYLE);

		m_font.setFamily(m_settings->value(settings::keys::FONT_FAMILY).toString());
		if (not m_font.exactMatch()) m_font.setFamily(defaults::FONT_FAMILY);

		m_settings->endGroup();
	}


	void PomodoroTimerWidget::writeDefaultSettings() const
	{
	    //TODO: Добавить дефолтный конфиг, который будет парситься при необходимости
		using enum impl::PomodoroTimer::Phase;
		m_settings->beginGroup(settings::groups::POMODORO_TIMER);

		auto writeValue = [&](const QString &key, const quint16 current)
		{
			if (not m_settings->contains(key)) m_settings->setValue(key, current);
		};

		for (auto i{0}; i != phaseMeta.keyCount(); ++i)
		{
			writeValue( settings::keys::PHASE_DURATIONS.at(i), defaults::PHASE_DURATIONS.at(i) );
		}

		writeValue(settings::keys::SESSION_LENGTH, m_timer->sessionLength());

		m_settings->endGroup();

		m_settings->beginGroup(settings::groups::STYLE);
		m_settings->setValue(settings::keys::FONT_FAMILY, m_font.family());
		m_settings->endGroup();
	}


	PomodoroTimerWidget::PomodoroTimerWidget(QWidget *parent) : QWidget{parent}
	{
		setObjectName("PomodoroTimerWidget");
	    setLayout(m_mainLayout);
        setFont(m_font);

        setupWidget();
        setupConnections();

		writeDefaultSettings();
        readSettings();
	}


	void PomodoroTimerWidget::updatePhaseLabelText(const impl::PomodoroTimer::Phase current) const
    {
		m_phaseLabel->setText(c_phaseStrings[qToUnderlying(current)]);
	}


	void PomodoroTimerWidget::updateStartPauseButtonText(const impl::PomodoroTimer::State current) const
    {
		m_startPauseButton->setText(c_timerStateStrings[qToUnderlying(current)]);
	}


	void PomodoroTimerWidget::updateRemainingTimeText(const quint16 current) const
    {
		const auto minutes {current / 60};
		const auto seconds {current % 60};

		m_remainingTimeLabel->setText(QString::asprintf("%d:%02d", minutes, seconds));
	}


	void PomodoroTimerWidget::updatePhaseProgress() const
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


	void PomodoroTimerWidget::updateSkipBreakButtonVisibility(const impl::PomodoroTimer::Phase current) const
    {
		m_skipBreakButton->setHidden(current == impl::PomodoroTimer::Phase::Work);
	}
}
