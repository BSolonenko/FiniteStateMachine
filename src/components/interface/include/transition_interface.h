#pragma once
#include <string>

namespace fsm
{	class TransitionInterface
	{
	public:
		~TransitionInterface() = default;

		virtual const std::string& TargetState() const = 0;
		virtual void OnActivate() = 0;
		virtual void Update(const size_t dt) = 0;
		virtual void OnDeactivate() = 0;
		virtual bool Activate() const = 0;
	};
}
