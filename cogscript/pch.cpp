#include "pch.h"

void RandomizeData(Const<RawPtr> aData, Const<size> aSize)
{
	static std::random_device device;
	static Const<std::uniform_int_distribution<size>> d(MinOf<size>, MaxOf<size>);

	Const<size> num = aSize / sizeof size;
	for (size i = 0; i < num; ++i)
	{
		Const<size> value = d(device);
		memcpy(&reinterpret_cast<Ptr<u8>>(aData)[i * sizeof size], &value, sizeof value);
	}

	Const<size> value = d(device);
	size remaining = aSize - num * sizeof size;
	if (remaining > 0)
		memcpy(&reinterpret_cast<Ptr<u8>>(aData)[aSize - remaining], &value, remaining);
}
