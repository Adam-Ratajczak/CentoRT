#pragma once

class ITask {
public:
	virtual void Execute() const = 0;
	virtual void Dump() const = 0;
};
