#pragma once
#include "AbstractCommand.h"

class AbstractFunctionCommand : public AbstractCommand {
public:
	AbstractFunctionCommand( void(*callback)()) {
		this->commandIdentifier->functionPointer = callback;
		this->commandIdentifier->methodInstancePointer = nullptr;
		this->commandIdentifier->methodPointer = nullptr;
	};
	~AbstractFunctionCommand() {}
	virtual int execute(EventContext* context) = 0;
	inline virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { return (commandIdentifier->functionPointer == this->commandIdentifier->functionPointer); };
private:
};