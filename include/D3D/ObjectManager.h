#pragma once
#include "DxManager.h"
//#include "Sprite.h"
#include "InstanceRenderer.h"
#include "Light.h"

enum class ECamera : char{
	//Current,		// �������� ī�޶�
	Screen,			// ���� Ÿ�ٿ�
	Main,			// ���� ī�޶�
	UI,				// ȭ�� ���� ī�޶�
	MiniMap,
	Camera1,
	Camera2,
	Camera3,
};

class GameObject;
class Collider;

// ��ϵ� ������Ʈ�� �����ϰ� ��ȸ-���� ��Ű�� �Ŵ���
class ObjectManager : public IDxBasis, public ISingleton<ObjectManager>
{
private:
	// ������Ʈ ����Ʈ
	map<EObjType, forward_list<GameObject*> >	 m_ObjectList;		// ��ü ��ȸ�� ����Ʈ
	map<wstring, stack<GameObject*> >			 m_DisabledPull;	// ��� ���� Ǯ
	map<wstring, GameObject*>					 m_ProtoPull;		// ����� ������Ʈ Ǯ

	map<wstring, stack<Component*> >			 m_DisabledPullComp;// ��� ���� ������Ʈ Ǯ
	map<wstring, Component*>					 m_ComponentPull;	// ����� ������Ʈ

	forward_list<Collider*>						 m_ColliderList;	// �浹ü ����Ʈ
	forward_list<InstanceRenderer*>				 m_InstanceList;	// �ν��Ͻ̿� ����Ʈ

	map<wstring, vector<Sprite> > m_SpriteList;						// ��������Ʈ ����Ʈ
public:
	static map<UINT, GameObject*> KeyObjects;						// ���� ó���� ������Ʈ��
	static UINT					  KeyCount;							// Ű�� ������
	static map<ECamera, Camera*>  Cameras;							// ī�޶��
	static Camera*				  CurCamera;						// �������� ī�޶�
	static list<Light*>			  Lights;							// �����
	// ��ó�� �̺�Ʈ ��Ͽ�(�Լ�, ����, ����)
	static queue<tuple<void(*)(void*, void*), void*, void*> > PostFrameEvent;
public:
	void ProcessPostEvent()	noexcept;
	// txt ���� �б�
	bool ReadSpriteScript()	noexcept;
	// ī�޶� ����
	void SetCurCamera(const ECamera& eCamera)	noexcept;
	// ����Ʈ ��ȯ
	vector<Sprite>* GetSpriteList(const wstring_view& spriteName)	  noexcept;
	map<wstring, vector<Sprite> > & GetSpriteList()					  noexcept;
	forward_list<GameObject*>* GetObjectList(const EObjType& objType) noexcept;
	// ������Ʈ �������� (��� Ǯ�� �����ְų�, ���� Ǯ�� ��� �ʿ�)
	GameObject* TakeObject(const wstring_view& objName, const bool& pushObject = true) noexcept;
	bool SetProtoObject(GameObject* pObject)					noexcept;	// ���� Ǯ�� �߰�
	void PushObject(GameObject* pObject, const bool& isPostEvent = true)	noexcept;	// ������Ʈ ����Ʈ�� �߰�
	void PopObject(GameObject* pObject)							noexcept;	// ������Ʈ ����Ʈ���� ������
	void DisableObject(GameObject* pObject)						noexcept;	// ������Ʈ ��Ȱ��ȭ(->��� Ǯ)
	bool RemoveObject(GameObject* pObject)						noexcept;	// ������Ʈ ����(���� �̺�Ʈ ���)
	// ������Ʈ ��������, ���, ����
	Component* TakeComponent(const wstring_view& compName)		noexcept;
	bool SetProtoComponent(Component* pComponent)				noexcept;
	void DisableComponent(Component* pComponent)				noexcept;	// ������Ʈ ��Ȱ��ȭ(->��� Ǯ)
	bool RemoveComponent(Component* pComponent)					noexcept;	// ������Ʈ ����("")
	// �浹ü ����Ʈ �߰�, ����
	forward_list<Collider*>& GetColliderList()					noexcept;
	void PushCollider(Collider* pCollider, const bool& isPostEvent = true)	noexcept;
	void PopCollider(Collider* pCollider, const bool& isPostEvent = true)	noexcept;

	// �ν��Ͻ� ����Ʈ �ֱ�, ����
	InstanceRenderer* PushInstance(InstanceRenderer* pInstance) noexcept;
	void PopInstance(InstanceRenderer* pInstance)				noexcept;				

	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
private:
	friend class ISingleton<ObjectManager>;
	friend class Dialog_Preset;
	friend class GameScene;
	ObjectManager() = default;
public:
	virtual ~ObjectManager() = default;
};