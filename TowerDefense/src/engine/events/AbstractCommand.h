#pragma once

struct EventContext {};

class VoidClass {};

struct UniqueCommandIdentifier {
	void* methodInstancePointer;
	void(VoidClass::* methodPointer)();
	void(*functionPointer)();
};

class AbstractCommand {
public:
	AbstractCommand() {};
	~AbstractCommand() {};
	virtual int execute(EventContext* context) = 0;
	virtual bool compareCommandsIdentifier(UniqueCommandIdentifier* commandIdentifier) = 0;
private:
};