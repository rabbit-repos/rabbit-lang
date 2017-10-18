#pragma once

class Symbol
{
protected:
	Symbol();

public:
	virtual ~Symbol();

	virtual String GetIdentifier() = 0;

private:

};
