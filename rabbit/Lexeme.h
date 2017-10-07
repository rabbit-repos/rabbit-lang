#pragma once

class Lexeme
{
public:
	Lexeme();
	virtual ~Lexeme();

	virtual void AppendData(Ref<List<u8>> aData) = 0;
};
