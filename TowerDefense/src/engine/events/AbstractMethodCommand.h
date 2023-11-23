#pragma once
#include "AbstractCommand.h"



template<typename T>
class AbstractMethodCommand : public AbstractCommand {
public:
	
	AbstractMethodCommand(T methodInstancePointer, void(T::* methodPointer)()) {
		this->commandIdentifier = { void* methodInstancePointer , (void(VoidClass::*)()) methodPointer, nullptr }
		this->methodInstancePointer = methodInstancePointer;
		this->methodPointer = methodPointer;
	};

	~AbstractMethodCommand() {}
	virtual int execute(EventContext* context) {
		methodInstancePointer->methodPointer();
	};
	virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { return (
		commandIdentifier->methodInstancePointer == this->commandIdentifier->methodInstancePointer 
		&& 
		commandIdentifier->methodPointer == this->commandIdentifier->methodPointer); 
	};

protected:
	T methodInstancePointer;
	void(T::* methodPointer)()
};