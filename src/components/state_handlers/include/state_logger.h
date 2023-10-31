#pragma once
#include <ostream>
#include "state_handler_interface.h"

namespace fsm
{
	namespace state_handler
	{
		class StateLogger : public StateHandlerInterface
		{
		public:
			explicit StateLogger(std::ostream& stream);

		private:
			void OnJoinedToState(const std::string& stateName) override;
			void OnEnter() override;
			void Update(const size_t) override {};
			void OnExit() override;

			std::ostream& m_logStream;
			std::string m_stateName;
		};
	}
}
