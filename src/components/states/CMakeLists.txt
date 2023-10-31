project(StateImpl)

MakeStaticLibraryStructure(INTERFACE_NAME FSM 
                            PRIVATE_LIBS 
                                FSM::Interface 
                                FSM::FsmImpl)
