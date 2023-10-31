#pragma once
#include <string>

namespace fsm
{
	class FSMControllerInterface
	{
	public:
		virtual ~FSMControllerInterface() = default;
		virtual void SwitchToState(const std::string& targetState) = 0;
	};
}
