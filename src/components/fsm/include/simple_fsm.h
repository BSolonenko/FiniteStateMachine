#pragma once
#include <map>
#include <memory>
#include <string>
#include "fsm_interface.h"
#include "fsm_controller_interface.h"

namespace fsm
{
	class SimpleFSM
		: public FSMInterface
		, public FSMControllerInterface
	{
	public:
		~SimpleFSM();

		void Start() override;
		void Start(const std::string& entryPoint) override;
		void Update(const size_t dt) override;
		void Finish() override;

		bool HasState(const std::string& name) const override;
		std::weak_ptr<StateInterface> GetState(const std::string& name) override;
		std::weak_ptr<StateInterface> GetCurrentState() override;

		std::string GetFullCurrentStatePathName() override;

		bool Started() const override;
	private:
		bool AddStateImpl(std::shared_ptr<StateInterface> state);

		void SwitchToState(const std::string& targetState) override;

		std::map<std::string, std::shared_ptr<StateInterface>> m_fsm;
		std::string m_entryPoint;
		std::string m_currentState;
	};


}
