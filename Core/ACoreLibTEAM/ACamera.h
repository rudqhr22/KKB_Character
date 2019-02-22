#pragma once
#include "AFrustum.h"
#include "ADevice.h"
//#include "KArcBall.h"

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08

class ACamera : public AFrustum
{
public:
	//ACamera*				m_pMainCamera;
	//KArcBall				m_WorldArcBall;
	//KArcBall				m_ViewArcBall;
	//KDevice				kdevice;
	//D3DXVECTOR3			m_vModelCenter;
	//D3DXMATRIX			m_mModelLastRot;        // Last arcball rotation matrix for model 
	//D3DXMATRIX			m_mModelRot;            // Rotation matrix of model
	//D3DXMATRIX			m_mCameraRotLast;
	D3DXMATRIX			m_matWorld;

	D3DXMATRIX			m_matView;
	D3DXMATRIX			m_matProj;


	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vTarget;
	D3DXVECTOR3			m_vUp;

	D3DXVECTOR3			m_vLook;
	D3DXVECTOR3			m_vSide;

	D3DXQUATERNION		m_qRotation;
	
	D3DXVECTOR3			m_vDefaultEye;
	D3DXVECTOR3			m_vDefaultLookAt;

	float m_fSpeed;
	float m_fPitch;		//X��
	float m_fYaw;		//Y��
	float m_fRoll;

	//--------------------------------------------------------------------------------------
	// ���콺 �� ��ư�� ��뿩�θ� �Ǵ��ϴ� ����ũ ���� ���콺 �� ������
	//--------------------------------------------------------------------------------------	
	int					m_nMouseWheelDelta;     // Amount of middle wheel scroll (+/-) 
	int					m_nRotateModelButtonMask;
	int					m_nZoomButtonMask;
	int					m_nRotateCameraButtonMask;

	//  ������( �ʱ� �������κ����� �Ÿ�) �� ���� ���� 
	float				m_fRadius;
	float				m_fDefaultRadius;       // Distance from the camera to model 
	float				m_fMinRadius;           // Min radius
	float				m_fMaxRadius;           // Max radius
public:
	
	D3DXMATRIX*			GetWorldMatrix() { return &m_matWorld; };
	D3DXMATRIX*			GetViewMatrix() { return &m_matView; }
	D3DXMATRIX*			GetProjMatrix() { return &m_matProj; }
	D3DXVECTOR3*		GetEyePt() { return &m_vPos; }
	//bool Set(int iwidth, int height);

	bool SetViewMatrix(D3DXVECTOR3 vPos, 
		D3DXVECTOR3 vTargetD3DXVECTOR3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	D3DXMATRIX SetObjectView(D3DXVECTOR3 vMax, D3DXVECTOR3 vMin);
	virtual D3DXMATRIX UpdateVector();
	D3DXMATRIX Update(D3DXVECTOR4 vDirValue);


	D3DXVECTOR3*		GetRightVector() { return &m_vSide; }
	D3DXVECTOR3*		GetLookVector() { return &m_vLook; }
	D3DXVECTOR3*		GetUpVector() { return &m_vUp; }


	virtual D3DXMATRIX			SetProjMatrix(FLOAT fFOV,
		FLOAT fAspect,
		FLOAT fNearPlane,
		FLOAT fFarPlane);

	//--------------------------------------------------------------------------------------
	// ���� ����� �Ӽ�����
	//--------------------------------------------------------------------------------------	
	float				m_fFOV;                 // Field of view
	float				m_fAspect;              // Aspect ratio
	float				m_fNearPlane;           // Near plane
	float				m_fFarPlane;            // Far plane

												// �߰� : ���Ϸ� �� ���� 	
	float				m_fCameraYawAngle;
	float				m_fCameraPitchAngle;
	float				m_fCameraRollAngle;
	
	float				GetYawAngle() { return m_fCameraYawAngle; }
	float				GetPitchAngle() { return m_fCameraPitchAngle; }
	float				GetRollAngle() { return m_fCameraRollAngle; }


	virtual void				MoveLook(float fValue);
	virtual void				MoveSide(float fValue);
	virtual void				MoveUp(float fValue);

	void						SetRadius(float fDefaultRadius = 5.0f, float fMinRadius = 1.0f, float fMaxRadius = FLT_MAX);

public:
//	bool		Init();
virtual 	bool		Frame();
//	bool		Render();
//	bool		Release();
public:
	ACamera();
	virtual~ACamera();
};

