#pragma once
#include "AbstractCommand.h"

class AbstractMethodCommand {
public:
	AbstractMethodCommand(void(*)() callback) {
		this->functionPointer = (void(*)())callback;
	};
	~AbstractMethodCommand() {}
	virtual int execute(EventContext* context) = 0;
	virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) { 
		if (commandIdentifier->methodInstancePointer == this->methodInstancePointer && commandIdentifier->methodPointer == this->methodPointer) return true; };
private:
	void(*)() functionPointer;
};