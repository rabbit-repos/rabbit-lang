#pragma once

class TokenContext
{
public:
	TokenContext();
	TokenContext(String aData);
	~TokenContext();

	ConstRef<String> GetData() const;

private:
	String mySourceLine;
	String myData;
	String myNextToken;
	String myPreviousToken;
};
