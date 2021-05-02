#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

BEGIN(Engine)
class ENGINE_DLL CTransformComponent
{
protected:
	GETTOR_SETTOR(matrix4x4, m_worldMat, {}, WorldMatrix)
	GETTOR_SETTOR(vector3, m_position, vector3(0, 0, 0), Position)
	GETTOR_SETTOR(vector3, m_rotation, vector3(0, 0, 0), Rotation)
	GETTOR_SETTOR(vector3, m_scale, vector3(1, 1, 1), Scale)

	GETTOR_SETTOR(CGameObject*, m_target, nullptr, Target)
		GETTOR_SETTOR(_float, m_cameraX, 0, CameraX)
	GETTOR_SETTOR(_float, m_cameraY, 0, CameraY)
	GETTOR_SETTOR(_bool, m_camera, false, Camera)
public:
	explicit	CTransformComponent(void);
	~CTransformComponent(void);

protected:
	void TransformUpdate();
public:
	vector3 ReturnTranslate(vector3 translation);
	vector3 ReturnPosTranslate(vector3 translation);
	void OutTranslate(vector3& translation);
	void Translate(vector3 translation);
	void CameraDirTranslate(vector3 translation);
	void MoveTowards(vector3 targetPosition, _float speed);
	void Lerp(vector3 targetPosition, _float speed);
	void LookAt(vector3 target, vector3 worldUp = vector3Forward);

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

	void SetScaleX(_float x) { m_scale.x = x; }
	void SetScaleY(_float y) { m_scale.y = y; }
	void SetScaleZ(_float z) { m_scale.z = z; }

	void AddCameraY(_float y) { m_cameraY += y; }

	matrix4x4* GetWorldMatrixPoint() { return &m_worldMat; }
	void AddWorldMatrix(matrix4x4 mat) { m_worldMat *= mat; }
private:
	void UpdateWorldmMatrix(void);
};
END
#endif