#pragma once
#include "Transform.h"
//#include "Component.h"
//#include "Physics.h"
#include "Collider.h"



enum class EObjType : char {
	Dummy,
	Map,
	Object,
	Character,
	Enemy,
	AObject,
	//Image,
	Camera,
	Light,
	Effect,
	UI,
};


// ������Ʈ�� ��� ������ �⺻ Ŭ����
class GameObject : public Transform, public IDxBasis, public Physics
{
protected:
	GameObject*								   m_pParent = nullptr;	 // �θ� ������
	forward_list<GameObject*>				   m_childList;			 // �ڽ� ����Ʈ
	map<EComponent, forward_list<Component*> > m_components;		 // ������Ʈ ����Ʈ

	D3DXMATRIX m_matLocal;											 // Local ���
	D3DXMATRIX m_matScale	 = Matrix::Identity;					 // Scale ���
	D3DXMATRIX m_matRotation = Matrix::Identity;					 // Rotation ���
																	 
	bool  m_isEnable	= true;										 // Ȱ��ȭ ����
	bool  m_isGlobal	= false;									 // ObjectManager ������� ���� ����
	bool  m_isStatic	= false;									 // SRT ���� ����
	bool  m_isBillBoard = false;									 // ������ ��� ���� ����
																	 
	float m__;	// �Ⱦ�											   
public:																 
	UINT	 m_keyValue;											 // ������ Ű��
	wstring	 m_myName;												 // ��ü �̸�
	EObjType m_objType = EObjType::Dummy;							 // ��ü Ÿ��
public:
	virtual void UpdateMatrix()												noexcept;
	// ������Ʈ �߰�, ����, �˻�
	void AddComponent(Component* pComponent)								noexcept;
	void AddComponent(const initializer_list<Component*>& components)		noexcept;
	void RemoveComponent(Component* pComponent)								noexcept;
	//template <typename Type>
	//Type*		 GetComponent()												noexcept;
	Component*	 GetComponent(const EComponent& eCompType)					noexcept;
	forward_list<Component*>* GetComponentList(const EComponent& eCompType) noexcept;
	map<EComponent, forward_list<Component*> >& GetComponentList()			noexcept;
	Collider*	 GetCollider()												noexcept;
	// �θ� ����
	virtual void SetParent(GameObject* pParent)						  	    noexcept;
	GameObject*  GetParent()										  const noexcept;
	GameObject*  GetRoot()											  	    noexcept;
	void		 CutParent(const bool& pushObject = true) noexcept;
	void		 CutParent(const bool& pushObject, const bool& isPostEvent) noexcept;
	forward_list<GameObject*>* GetChildList()						  	    noexcept;
	// �θ���� * �ڽķ���
	void SetWorldPosition(const D3DXVECTOR3& position)						noexcept;
	void SetWorldRotation(const D3DXQUATERNION& rotation)					noexcept;
	void SetWorldScale(const D3DXVECTOR3& scale)							noexcept;
	D3DXVECTOR3	   GetWorldPosition()								  const noexcept;
	D3DXQUATERNION GetWorldRotation()								  const noexcept;
	D3DXVECTOR3	   GetWorldScale()									  const noexcept;
	// ��� ����, ��ȯ
	void  SetWorldMatrix(const D3DXMATRIX& matWorld)						noexcept;
	const D3DXMATRIX& GetWorldMatrix()								  const noexcept;
	const D3DXMATRIX& GetScaleMatrix()								  const noexcept;
	const D3DXMATRIX& GetRotationMatrix()							  const noexcept;

	void SetKeyValue(const UINT& keyValue)									noexcept;

	bool isEnable()															noexcept;
	void isEnable(const bool& isEnable, const bool& putDisablePool = false) noexcept;
	bool isGlobal()															noexcept;
	void isGlobal(const bool& isGlobal)										noexcept;
	bool isStatic()															noexcept;
	void isStatic(const bool& isStatic)										noexcept;
	bool isBillBoard()														noexcept;
	void isBillBoard(const bool& isBillBoard)								noexcept;

	virtual bool Init()														noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)				noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)						noexcept override;
	virtual bool Release()													noexcept override;
	virtual GameObject* clone()												noexcept;		// �ڱ� ��ü ���� ��ȯ
protected:
	GameObject* cloneChild(GameObject* pObject)								noexcept;		// �ڽ� ������
protected:
	friend class AseParser;
	friend class MaxImporter;
	friend class Dialog_Hierarchy;
	friend class CAnimation;
public:
	GameObject() = default;
	GameObject(const wstring_view& myName, const EObjType& eType = EObjType::Dummy);
	GameObject(const wstring_view& myName, const std::initializer_list<Component*>& components, const EObjType& eType = EObjType::Dummy);
	GameObject(const wstring_view& myName, Component* pComponent, const EObjType& eType = EObjType::Dummy);
	virtual ~GameObject() noexcept = default;
};


//template <typename Type>
//Type* GameObject::GetComponent() noexcept
//{
//	for (auto& iter : m_components)
//	{
//		if (std::is_base_of<iter.second.front(), Type*>::value)
//		{
//			return iter.second.front();
//		}
//	}
//	return nullptr;
//}