#pragma once

class Symbol
{
protected:
	Symbol(String aIdentifier);

public:
	virtual ~Symbol();

	ConstRef<String> GetIdentifier() const;

private:
	String myIdentifier;
};
