#ifndef MYDEFINE_H
#define MYDEFINE_H

#define DEFAULT = default
#define NONE {}

#ifndef ENGINE_MODE
#define EDITOR_MODE
#endif


//Update Event Define
#define NO_EVENT		0
#define SCENE_CHANGE	1
#define NULL_PARAMETER	2
#define OUT_OF_RANGE	3

#define KEY_LEFT	1
#define KEY_RIGHT	2
#define KEY_UP		4
#define KEY_DOWN	8
#define KEY_SPACE	16
#define KEY_RETURN	32
#define MOUSE_LEFT	64
#define MOUSE_RIGHT	128
#define KEY_F1		256
#define KEY_F2		512
#define KEY_F3		1024
#define KEY_F4		2048
#define KEY_F5		4096
#define KEY_W		8192
#define KEY_A		16384
#define KEY_S		32768
#define KEY_D		65536
#define KEY_SHIFT	131072
#define KEY_RBUTTON	262144
#define KEY_1       524288
#define KEY_2       1048576
#define KEY_3		2097152
#define KEY_4		4194304
#define KEY_TAB		8388608
#define KEY_DELETE	16777216
#define KEY_Q		33554432
#define KEY_X		67108864
#define KEY_LBUTTON	134217728
#define KEY_E	    268435456

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define GRAVITY			vector3(0,  -9.807f, 0)

#define vector3Zero		vector3(0,  0,  0)
#define vector3One		vector3(1,  1,  1)
#define vector3Right	vector3(1,  0,  0)
#define vector3Left		vector3(-1, 0,  0)
#define vector3Up		vector3(0,  1,  0)
#define vector3Down		vector3(0,  -1, 0)
#define vector3Forward	vector3(0,  0,  1)
#define vector3Back		vector3(0,  0, -1)

#define PI 3.141592f
#define EPSILON 0.0003f

#endif // !MYDEFINE_H

