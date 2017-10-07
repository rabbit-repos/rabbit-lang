#pragma once

enum class VirtualListCopyMode : u8
{
	MoveConstruct,
	CopyConstruct,
	MoveAssign,
	CopyAssing,
	Destruct
};

template <typename T>
void VirtualCopyHelper(Const<Ptr<void>> aDestination, Const<Ptr<void>> aSource, Const<VirtualListCopyMode> aCopyMode)
{
	Ptr<T> destination = reinterpret_cast<Ptr<T>>(aDestination);

	switch (aCopyMode)
	{
	case VirtualListCopyMode::MoveConstruct:
		new (destination) T(std::move(*reinterpret_cast<Ptr<T>>(aSource)));
		break;
	case VirtualListCopyMode::CopyConstruct:
		new (destination) T(*reinterpret_cast<ConstPtr<T>>(aSource));
		break;

	case VirtualListCopyMode::MoveAssign:
		*destination = std::move(*reinterpret_cast<Ptr<T>>(aSource));
		break;
	case VirtualListCopyMode::CopyAssing:
		*destination = *reinterpret_cast<ConstPtr<T>>(aSource);
		break;

	case VirtualListCopyMode::Destruct:
		reinterpret_cast<Ptr<T>>(aSource)->~T();
		break;

	default:
		abort();
	}
}
