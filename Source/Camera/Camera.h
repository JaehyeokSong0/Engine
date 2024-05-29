#pragma once

/* MEMO
* XMLoadFloat() : XMFLOAT to XMVECTOR 
  XMStoreFloat() : XMVECTOR to XMFLOAT
*/

const XMFLOAT3 XMFLOAT3_ZERO= XMFLOAT3(0.0f, 0.0f, 0.0f);
const XMVECTOR DEFAULT_EYE = { 0.0f, 0.0f, 0.0f };
const XMVECTOR DEFAULT_AT = { 0.0f, 0.0f, 1.0f };
const XMVECTOR DEFAULT_UP = { 0.0f, 1.0f, 0.0f };

class Camera final
{
public:
	Camera();
	~Camera() = default;

	void Initialize(XMVECTOR position = DEFAULT_EYE, XMVECTOR rotation = DEFAULT_AT);
	void Update();

	void SetPosition(XMFLOAT3 position);
	void SetPosition(XMVECTOR position);
	void SetRotation(XMFLOAT3 rotation);
	void SetRotation(XMVECTOR rotation);

	const XMMATRIX GetViewMatrix() const;
	const XMMATRIX GetRotationMatrix() const;

	// Input parameter만큼 transform update
	void Move(XMVECTOR inputPos);
	void Move(XMFLOAT3 inputPos);
	void Rotate(XMVECTOR inputRot);
	void Rotate(XMFLOAT3 inputRot);

private:
	XMFLOAT3 position;
	XMFLOAT3 rotation;

	XMVECTOR positionVector;
	XMVECTOR rotationVector;

	XMMATRIX viewMatrix;
	XMMATRIX rotationMatrix;
	XMMATRIX projectionMatrix;

	void UpdateViewMatrix();
	void UpdateRotationMatrix();
};


// TODO : SetProjectionMatrix.. 아마