#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTransformComponent
{
protected:
	GETTOR(matrix4x4, m_worldMat, {}, WorldMatrix)
	GETTOR_SETTOR(vector3, m_position, vector3(0, 0, 0), Position)
	GETTOR_SETTOR(vector3, m_rotation, vector3(0, 0, 0), Rotation)
	GETTOR_SETTOR(vector3, m_scale, vector3(1, 1, 1), Scale)

public:
	explicit	CTransformComponent(void);
	~CTransformComponent(void);

protected:
	void TransformUpdate();
public:
		 
	void Translate(vector3 translation);
	void MoveTowards(vector3& thisPosition, vector3 targetPosition, _float speed);
	void Lerp(vector3& thisPosition, vector3 targetPosition, _float speed);
		 
	void SetPositionX(_float x) { m_position.x = x; }
	void SetPositionY(_float y) { m_position.y = y; }
	void SetPositionZ(_float z) { m_position.z = z; }
		 
	void AddPosition(vector3 xyz) { m_position += xyz; }
	void AddPositionX(_float x) { m_position.x += x; }
	void AddPositionY(_float y) { m_position.y += y; }
	void AddPositionZ(_float z) { m_position.z += z; }
		 
	void SetRotationX(_float x) { m_rotation.x = x; }
	void SetRotationY(_float y) { m_rotation.y = y; }
	void SetRotationZ(_float z) { m_rotation.z = z; }
		 
	void AddRotationX(_float x) { m_rotation.x += x; }
	void AddRotationY(_float y) { m_rotation.y += y; }
	void AddRotationZ(_float z) { m_rotation.z += z; }
private:
	void				UpdateWorldmMatrix(void);
};
END
#endif