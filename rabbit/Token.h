#pragma once

class Token
{
public:
	Token();
	virtual ~Token();

	virtual void AppendData(Ref<List<u8>> aData) = 0;
};
