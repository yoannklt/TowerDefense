#pragma once
#include "AbstractCommand.h"

class AbstractFunctionCommand : AbstractCommand {
public:
	AbstractFunctionCommand(void* callback) {
		this->functionPointer = (void*)callback;
	};
	~AbstractFunctionCommand() {}
	virtual int execute(EventContext* context) = 0;
	virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { if (commandIdentifier->functionPointer == this->functionPointer) return true; };
private:
	void* functionPointer;
};