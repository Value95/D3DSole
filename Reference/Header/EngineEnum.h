#ifndef ENGINEENUM_H
#define ENGINEENUM_H

namespace Engine
{
	enum class EDisplayMdoe
	{
		FullMode,
		WinMode
	};

	enum class ERenderID
	{
		Base,
		NumOfRenderID
	};

	enum class EColliderType
	{
		Box,
		Sphere
	};

	enum CHANNELID
	{
		MOVE,
		ROAR,
		BGM,
		ATTACK,
		MAXCHANNEL
	};
}
#endif // !ENGINEENUM_H
