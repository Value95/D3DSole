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
		PLAYER,
		LAND_HUMAN,
		LAND,
		JUMP,
		DOOR,
		BOX,
		HAT,
		UI,
		BGM,
		MAXCHANNEL
	};
}
#endif // !ENGINEENUM_H
