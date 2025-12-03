/**
 * @date 11/14/25
 * 
 * @author amitayus_
 */

#pragma once


#include <QObject>
#include <QTimer>

#include <chrono>


namespace paz::impl::pt
{
  /**
	 * @brief Враппер над QTimer для реализации логики таймера помодоро.
	 *
	 * @details Хранит время начала отсчета и оставшееся время таймера.
	 *					И возвращает сигналы по тикам и окончанию таймера.
	 */

	class TimerEngine final : public QObject
	{
		Q_OBJECT

	public:

		/**
		 * @brief Дефолтный конструктор.
		 *
		 * @details Вызывает конструктор.
		 *					`TimerEngine::TimerEngine(std::chrono::seconds startTime, std::chrono::seconds timeLeft, QObject* parent)`.
		 *					Значения `m_startTime` и `m_timeLeft` задаются нулем.
		 *
		 * @param parent Указатель на родительский QObject.
		 */

		explicit TimerEngine(QObject* parent = nullptr);

		/**
		 * @brief Конструктор с установкой времени начала отсчета таймера.
		 *
		 * @details Вызывает конструктор
		 *				  `TimerEngine::TimerEngine(std::chrono::seconds startTime, std::chrono::seconds timeLeft, QObject* parent)`.
		 *				  Значение `m_timeLeft` устанавливается равным `startTime.
		 *
		 * @param startTime  Время начала отсчета таймера в std::chrono::seconds.
		 * @param parent Указатель на родительский QObject.
		 */

		explicit TimerEngine(std::chrono::seconds	startTime, QObject* parent = nullptr);

		/**
		 * @brief Конструктор с установкой времени начала отсчета и оставшегося времени таймера.
		 *
		 * @details Инициализирует `m_startTime` и `m_timeLeft` переданными значениями.
		 *					Если `timeLeft` больше `startTime`, то `m_timeLeft` присваивается значение `startTime`.
		 *
		 * @param startTime Время начала отсчета таймера в std::chrono::seconds.
		 * @param timeLeft Оставшееся время таймера в std::chrono::seconds.
		 * @param parent Указатель на родительский QObject.
		 */

		TimerEngine(std::chrono::seconds startTime, std::chrono::seconds timeLeft, QObject *parent = nullptr);

		/**
		 * @brief Геттер для получения времени начала отсчета таймера.
		 *
		 * @return Возвращает время начала отсчета таймера в std::chrono::seconds.
		 */

		[[nodiscard]] auto startTime() const -> std::chrono::seconds;

		/**
		 *	@brief Геттер для получения оставшегося времени таймера.
		 *
		 * @return Возвращает оставшееся время таймера в std::chrono::seconds.
		 */

		[[nodiscard]] auto timeLeft() const -> std::chrono::seconds;

		/**
		 * @brief Проверяет, активен ли таймер.
		 *
		 * @details Враппер над `QTimer::isActive()`.
		 *
		 * @return Возвращает `true`, если таймер активен.
		 */

		[[nodiscard]] bool isActive() const;

	public slots:

		/**
		 * @brief Сеттер для установки времени начала отсчета таймера.
		 *
		 * @details Если новое значение меньше `m_startTime`, то к `m_timeLeft` также присваивается новое значение.
		 *
		 * @param duration Новое значение в std::chrono::seconds.
		 */

		void setStartTime(std::chrono::seconds duration);

		/**
		 * @brief Сеттер для установки оставшегося времени таймера.
		 *
		 * @details Если новое значение больше `m_timeLeft`, то присваивается текущее значение `m_timeLeft`.
		 *
		 * @param duration Новое значение в std::chrono::seconds.
		 */

		void setTimeLeft(std::chrono::seconds duration);

		/**
		 * @brief Сеттер для установки нового времени таймера.
		 *
		 * @details Присваивает к `m_startTime` и `m_timeLeft` новое значение.
		 *
		 * @note Название метода - кал, стоит поменять. Да и существование метода под вопросом.
		 *
		 * @param duration Новое значение в std::chrono::seconds.
		 */

		void setNewTimer(std::chrono::seconds duration);

		/**
		 * @brief Запускает таймер.
		 *
		 * @details Запускает внутренний QTimer `m_timer`.
		 */

		void start();

		/**
		 * @brief Останавливает таймер.
		 *
		 * @details Останавливает внутренний QTimer `m_timer`.
		 */

		void stop();

		/**
		 * @brief Сбрасывает таймер и останавливает его.
		 *
		 * @details Присваивает `m_timeLeft` значение `m_startTime` и останавливает внутренний QTimer `m_timer`.
		 */

		void resetAndStop();

	private slots:

		/**
		 * @brief Слот, вызываемый по тикам внутреннего QTimer `m_timer`.
		 *
		 * @details Уменьшает `m_timeLeft` на 1 секунду.
		 *					Если `m_timeLeft` достигает нуля, то испускается сигнал `timerFinished()`
		 *					и таймер сбрасывается и останавливается.
		 *					Иначе испускается сигнал `timerTicked()`.
		 */

		void handleTick();

	signals:

		/**
		 * @brief Сигнал, испускаемый при запуске таймера.
		 *
		 * @details Испускается в слоте `start()`.
		 */

		void timerStarted();

		/**
		 * @brief Сигнал, испускаемый при остановке таймера.
		 *
		 * @details Испускается в слоте `stop()`.
		 */

		void timerStopped();

		/**
		 * @brief Сигнал, испускаемый по тикам таймера.
		 *
		 * @details Испускается слотом `handleTick()` после обработки тика `m_timer.timeout()`.
		 *
		 * @param timeLeft Значение поля m_timeLeft.
		 */

		void timerTicked(std::chrono::seconds timeLeft);

		/**
		 * @brief Сигнал, испускаемый при окончании таймера.
		 *
		 * @details Испускается слотом `handleTick()` когда `m_timeLeft` достигает нуля.
		 */

		void timerFinished();

		/**
		 * @brief Сигнал, испускаемый при изменении времени начала отсчета таймера.
		 *
		 * @details Испускается в сеттере `setStartTime()`.
		 *
		 * @param newStartTime Новое значение `m_startTime`.
		 */

		void startTimeChanged(std::chrono::seconds newStartTime);

		/**
		 * @brief Сигнал, испускаемый при изменении оставшегося времени таймера.
		 *
		 * @details Испускается в сеттере `setTimeLeft()`.
		 *
		 * @param newTimeLeft  Новое значение `m_timeLeft`.
		 */
		void timeLeftChanged(std::chrono::seconds newTimeLeft);

	private:

		QTimer m_timer; /// Внутренний QTimer для реализации логики таймера.

		std::chrono::seconds m_startTime; /// Время начала отсчета таймера.
		std::chrono::seconds m_timeLeft; /// Оставшееся время таймера.
	};
}