#pragma once
#include <string>

namespace fsm
{
	class StateHandlerInterface
	{
	public:
		virtual ~StateHandlerInterface() = default;

		virtual void OnJoinedToState(const std::string& stateName) = 0;

		virtual void OnEnter() = 0;
		virtual void Update(const size_t dt) = 0;
		virtual void OnExit() = 0;
	};
}
