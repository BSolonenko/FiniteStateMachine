#include <iostream>
#include <memory>
#include "simple_fsm.h"
#include "state.h"
#include "state_logger.h"
#include "timer_transition.h"
#include "predicat_transition.h"
#include <chrono>

#include <Windows.h>

void fsmbuilder(const std::vector<std::pair<std::string, std::vector<std::string>>>& graph, std::weak_ptr<fsm::FSMInterface> fsmWeak, std::weak_ptr<fsm::FSMControllerInterface> controllerWeak)
{
	if (auto fsm = fsmWeak.lock())
	{
		std::map<std::string, std::shared_ptr<fsm::TransitionInterface>> transitions;
		for (const auto& link : graph)
		{
			const auto& from = link.first;
			if (auto state = fsm->AddState<fsm::State>(link.first).lock())
			{
				for (const auto& to : link.second)
				{
					if (transitions.count(to) == 0)
					{
						transitions[to] = std::make_shared<fsm::transition::Predicat>([to](const size_t) -> bool {
								for (int i = 0; i < 255; i++)
								{
									if (GetAsyncKeyState(i) & 0x8000)
									{
										std::string pressed;
										pressed += char(i);
										if (pressed == to)
										{
											return true;
										}
									}
								}
								return false;
							},to, controllerWeak);
					}

					state->AddTransition(transitions[to]);
				}
			}
		}
	}
}

int main()
{
	const auto fsm = std::make_shared<fsm::SimpleFSM>();
	std::vector<std::pair<std::string, std::vector<std::string>>> graph = {
		{"A", {"D", "H"}},
		{"B", {"C", "A"}},
		{"C", {"E"}},
		{"D", {"B"}},
		{"E", {"D", "F"}},
		{"F", {"G"}},
		{"G", {"C", "J"}},
		{"H", {"E"}},
		{"I", {"G", "H"}},
		{"J", {"I"}}
	};

	fsmbuilder(graph, fsm, fsm);

	if (fsm)
	{
		if (auto sharedState = fsm->GetState("A").lock())
		{
			sharedState->AddTransition(std::make_shared<fsm::transition::Timer>(1000, "J", fsm));
		}

		if (auto state = fsm->GetState("J").lock())
		{
			fsmbuilder(graph, state->GetSubFSM(), state->GetSubFSMController());
		}

		fsm->Start();
	}

	std::chrono::system_clock::time_point lastUpdate = std::chrono::system_clock::now();
	std::chrono::system_clock::duration lag(0);
	const std::chrono::system_clock::duration timeQuantum(std::chrono::milliseconds(15));

	while (true) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		lag += now - lastUpdate;
		lastUpdate = now;
		while (lag >= timeQuantum) {
			lag -= timeQuantum;
			if (fsm)
			{
				fsm->Update(std::chrono::duration_cast<std::chrono::milliseconds>(timeQuantum).count());
			}
		}
		if (fsm)
		{
			std::cout << fsm->GetFullCurrentStatePathName() << '\n';
		}
	}
	return 0;
}
