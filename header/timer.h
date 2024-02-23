#ifndef TIMER_H_
#define TIMER_H_

namespace game {

	// A class implementing a simple timer
	class Timer {

		public:
			// Constructor and destructor
			Timer(void);
			~Timer();

			// Start the timer now: duration given in seconds
			void Start(double duration);

			// Update the timer in the game loop;
			void Update(double delta_time);

			// Check timer status
			bool Finished(void) const;

		private:
			double end_time_;

	}; // class Timer

} // namespace game

#endif // TIMER_H_
