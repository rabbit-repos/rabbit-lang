#pragma once

class Symbol
{
protected:
	Symbol(String aIdentifier);

public:
	virtual ~Symbol();

	virtual String GetIdentifier() = 0;

private:
	String myIdentifier;
};
