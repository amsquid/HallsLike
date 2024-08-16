#include <string>

namespace hallslike {
	class Logger {
		public:
			void print(std::string message);
			void print(float message);
			void print(int message);
	};
}