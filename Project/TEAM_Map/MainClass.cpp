#include "MainClass.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "LobbyScene.h"


GameObject*					MainClass::m_pSkyBox	= nullptr;
map<ESceneName, MainClass*> MainClass::m_SceneList;
MainClass*				    MainClass::m_curScene	= nullptr;


void MainClass::MapInit()
{

	m_pHeightMap = new HeightMap(L"HeightMap", EComponent::Renderer, L"gamemap.png");
	auto pObject = new GameObject(L"HeightMap", m_pHeightMap, EObjType::Map);
	m_pHeightMap->CreateHeightMap(DxManager::GetDContext(), L"HeightMap/heightmap.png", 13.0f, 1.0f, 1.0f);
	m_pHeightMap->SetShadowRate(0.0f);

	//mapMap->SetEnviromentMap(((Renderer*)m_pSkyBox->GetComponent(EComponent::Renderer))->m_srcName, EEnviType::Fresnel);
	//pObject->Translate(Vector3::Down * 100.0f);
	
	
	m_pSkyBox = new GameObject(L"SkyBox", { new SkySphere(20, L"SkySphere", L"CubeMap/A_nightsky.dds"), new CTransformer(Vector3::Zero, Quaternion::Right * 0.02f, Vector3::Zero) }, EObjType::Dummy);
	m_pSkyBox->SetScale(Vector3::One * 100);
	m_pSkyBox->isGlobal(true);

	//pObject->SetScaleY(1.0f);
	ObjectManager::Get().PushObject(pObject);

	//////////////////////////////////////////////////////////////////////////////////////

	m_fountain.SetPlayerCharacter(L"MAP_FOUNTAIN", 0, 0, 0);
	m_fountain.SetScale(D3DXVECTOR3(6, 6, 6));
	m_fountain.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fountain);

	m_church.SetPlayerCharacter(L"MAP_Church", -450, 0, 450);	//280
	m_church.SetScale(D3DXVECTOR3(4, 4, 4));
	m_church.SetRotationY(67);
	m_church.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_church);

	m_blacksmith.SetPlayerCharacter(L"MAP_Blacksmith", 400, 0, 400);	//280
	m_blacksmith.SetScale(D3DXVECTOR3(0.6, 0.6, 0.3));
	m_blacksmith.SetRotationY(70);
	m_blacksmith.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_blacksmith);

	m_windmill.SetPlayerCharacter(L"MAP_WINDMILL", 450, 0, -450);	//280
	m_windmill.SetScale(D3DXVECTOR3(1.8, 1.8, 1.8));
	m_windmill.SetRotationY(PI*0.7);
	m_windmill.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_windmill);

	m_towerRound.SetPlayerCharacter(L"MAP_TowerRound", -420, 0, -420);	//280
	m_towerRound.SetScale(D3DXVECTOR3(1.6, 1.6, 1.6));
	m_towerRound.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_towerRound);


#pragma region MyHouse


	m_house00.SetPlayerCharacter(L"MAP_HOUSE_C", -680, 0, 680);	//280
	m_house00.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house00.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house00);
	m_house01.SetPlayerCharacter(L"MAP_HOUSE_B", -400, 0, 680);	//280
	m_house01.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house01.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house01);
	m_house02.SetPlayerCharacter(L"MAP_HOUSE_D", -680, 0, 400);	//280
	m_house02.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house02.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house02);


	m_house10.SetPlayerCharacter(L"MAP_HOUSE_C", 680, 0, 680);	//280
	m_house10.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house10.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house10);
	m_house11.SetPlayerCharacter(L"MAP_HOUSE_B", 400, 0, 680);	//280
	m_house11.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house11.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house11);
	m_house12.SetPlayerCharacter(L"MAP_HOUSE_D", 680, 0, 400);	//280
	m_house12.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house12.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house12);

	m_house20.SetPlayerCharacter(L"MAP_HOUSE_C", 680, 0, -680);	//280
	m_house20.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house20.SetRotationY(-PI);
	m_house20.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house20);
	m_house21.SetPlayerCharacter(L"MAP_HOUSE_B", 400, 0, -680);	//280
	m_house21.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house21.SetRotationY(-PI);
	m_house21.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house21);
	m_house22.SetPlayerCharacter(L"MAP_HOUSE_D", 680, 0, -400);	//280
	m_house22.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house22.SetRotationY(-PI);
	m_house22.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house22);

	m_house30.SetPlayerCharacter(L"MAP_HOUSE_C", -680, 0, -680);	//280
	m_house30.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house30.SetRotationY(-PI);
	m_house30.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house30);
	m_house31.SetPlayerCharacter(L"MAP_HOUSE_B", -400, 0, -680);	//280
	m_house31.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house31.SetRotationY(-PI);
	m_house31.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house31);
	m_house32.SetPlayerCharacter(L"MAP_HOUSE_D", -680, 0, -400);	//280
	m_house32.SetScale(D3DXVECTOR3(130, 130, 130));
	m_house32.SetRotationY(-PI);
	m_house32.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_house32);





#pragma endregion

#pragma region MyTower

	//상
	m_tower0.SetPlayerCharacter(L"MAP_Tower", 250, 0, 900);	//280;
	m_tower0.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));;
	m_tower0.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower0);

	m_tower1.SetPlayerCharacter(L"MAP_Tower", -250, 0, 900);	//280
	m_tower1.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));;
	m_tower1.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower1);


	//우
	m_tower2.SetPlayerCharacter(L"MAP_Tower", 900, 0, 250);	//280;
	m_tower2.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));
	m_tower2.SetRotationY(PI*0.5);
	m_tower2.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower2);

	m_tower3.SetPlayerCharacter(L"MAP_Tower", 900, 0, -250);	//280;
	m_tower3.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));
	m_tower3.SetRotationY(PI*0.5);
	m_tower3.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower3);

	//하
	m_tower4.SetPlayerCharacter(L"MAP_Tower", 250, 0, -900);	//280;
	m_tower4.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));
	m_tower4.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower4);

	m_tower5.SetPlayerCharacter(L"MAP_Tower", -250, 0, -900);	//280;
	m_tower5.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));
	m_tower5.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower5);

	//좌
	m_tower6.SetPlayerCharacter(L"MAP_Tower", -900, 0, 250);	//280;
	m_tower6.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));;
	m_tower6.SetRotationY(PI*0.5);
	m_tower6.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower6);

	m_tower7.SetPlayerCharacter(L"MAP_Tower", -900, 0, -250);	//280;
	m_tower7.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));;
	m_tower7.SetRotationY(PI*0.5);
	m_tower7.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tower7);


	m_towerTR.SetPlayerCharacter(L"MAP_Tower", 900, 0, 900);
	m_towerTR.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));;
	m_towerTR.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_towerTR);

	m_towerTL.SetPlayerCharacter(L"MAP_Tower", -900, 0, 900);
	m_towerTL.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));
	m_towerTL.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_towerTL);

	m_towerBR.SetPlayerCharacter(L"MAP_Tower", 900, 0, -900);
	m_towerBR.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));;
	m_towerBR.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_towerBR);

	m_towerBL.SetPlayerCharacter(L"MAP_Tower", -900, 0, -900);
	m_towerBL.SetScale(D3DXVECTOR3(0.8, 0.8, 0.8));
	m_towerBL.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_towerBL);

#pragma endregion

#pragma region MyWall
	//상
	m_wall00.SetPlayerCharacter(L"MAP_WALL", 402, 0, 900);
	m_wall00.SetRotationY(PI*-0.5);
	m_wall00.SetScaleZ(2.2f);
	m_wall00.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall00);

	m_wall01.SetPlayerCharacter(L"MAP_WALL", 575, 0, 900);
	m_wall01.SetRotationY(PI*-0.5);
	m_wall01.SetScaleZ(2.2f);
	m_wall01.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall01);

	m_wall02.SetPlayerCharacter(L"MAP_WALL", 748, 0, 900);
	m_wall02.SetRotationY(PI*-0.5);
	m_wall02.SetScaleZ(2.2f);
	m_wall02.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall02);

	m_wall03.SetPlayerCharacter(L"MAP_WALL", -402, 0, 900);
	m_wall03.SetRotationY(PI*-0.5);
	m_wall03.SetScaleZ(2.2f);
	m_wall03.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall03);

	m_wall04.SetPlayerCharacter(L"MAP_WALL", -575, 0, 900);
	m_wall04.SetRotationY(PI*-0.5);
	m_wall04.SetScaleZ(2.2f);
	m_wall04.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall04);

	m_wall05.SetPlayerCharacter(L"MAP_WALL", -748, 0, 900);
	m_wall05.SetRotationY(PI*-0.5);
	m_wall05.SetScaleZ(2.2f);
	m_wall05.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall05);


	//우
	m_wall10.SetPlayerCharacter(L"MAP_WALL", 900, 0, 402);
	m_wall10.SetScaleZ(2.2f);
	m_wall10.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall10);

	m_wall11.SetPlayerCharacter(L"MAP_WALL", 900, 0, 575);
	m_wall11.SetScaleZ(2.2f);
	m_wall11.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall11);

	m_wall12.SetPlayerCharacter(L"MAP_WALL", 900, 0, 748);
	m_wall12.SetScaleZ(2.2f);
	m_wall12.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall12);

	m_wall13.SetPlayerCharacter(L"MAP_WALL", 900, 0, -402);
	m_wall13.SetScaleZ(2.2f);
	m_wall13.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall13);

	m_wall14.SetPlayerCharacter(L"MAP_WALL", 900, 0, -575);
	m_wall14.SetScaleZ(2.2f);
	m_wall14.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall14);

	m_wall15.SetPlayerCharacter(L"MAP_WALL", 900, 0, -748);
	m_wall15.SetScaleZ(2.2f);
	m_wall15.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall15);

	//하
	m_wall20.SetPlayerCharacter(L"MAP_WALL", 402, 0, -900);
	m_wall20.SetRotationY(PI*0.5);
	m_wall20.SetScaleZ(2.2f);
	m_wall20.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall20);

	m_wall21.SetPlayerCharacter(L"MAP_WALL", 575, 0, -900);
	m_wall21.SetRotationY(PI*0.5);
	m_wall21.SetScaleZ(2.2f);
	m_wall21.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall21);

	m_wall22.SetPlayerCharacter(L"MAP_WALL", 748, 0, -900);
	m_wall22.SetRotationY(PI*0.5);
	m_wall22.SetScaleZ(2.2f);
	m_wall22.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall22);

	m_wall23.SetPlayerCharacter(L"MAP_WALL", -402, 0, -900);
	m_wall23.SetRotationY(PI*0.5);
	m_wall23.SetScaleZ(2.2f);
	m_wall23.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall23);

	m_wall24.SetPlayerCharacter(L"MAP_WALL", -575, 0, -900);
	m_wall24.SetRotationY(PI*0.5);
	m_wall24.SetScaleZ(2.2f);
	m_wall24.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall24);

	m_wall25.SetPlayerCharacter(L"MAP_WALL", -748, 0, -900);
	m_wall25.SetRotationY(PI*0.5);
	m_wall25.SetScaleZ(2.2f);
	m_wall25.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall25);


	//좌
	m_wall30.SetPlayerCharacter(L"MAP_WALL", -900, 0, 402);
	m_wall30.SetRotationY(-PI);
	m_wall30.SetScaleZ(2.2f);
	m_wall30.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall30);

	m_wall31.SetPlayerCharacter(L"MAP_WALL", -900, 0, 575);
	m_wall31.SetRotationY(-PI);
	m_wall31.SetScaleZ(2.2f);
	m_wall31.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall31);

	m_wall32.SetPlayerCharacter(L"MAP_WALL", -900, 0, 748);
	m_wall32.SetRotationY(-PI);
	m_wall32.SetScaleZ(2.2f);
	m_wall32.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall32);

	m_wall33.SetPlayerCharacter(L"MAP_WALL", -900, 0, -402);
	m_wall33.SetRotationY(-PI);
	m_wall33.SetScaleZ(2.2f);
	m_wall33.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall33);

	m_wall34.SetPlayerCharacter(L"MAP_WALL", -900, 0, -575);
	m_wall34.SetRotationY(-PI);
	m_wall34.SetScaleZ(2.2f);
	m_wall34.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall34);

	m_wall35.SetPlayerCharacter(L"MAP_WALL", -900, 0, -748);
	m_wall35.SetRotationY(-PI);
	m_wall35.SetScaleZ(2.2f);
	m_wall35.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wall35);


#pragma endregion

#pragma region MyTree

	m_tree00.SetPlayerCharacter(L"MAP_TREE1", -190, 0, 580);
	m_tree00.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree00);

	m_tree01.SetPlayerCharacter(L"MAP_TREE1", 190, 0, 580);
	m_tree01.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree01);

	m_tree02.SetPlayerCharacter(L"MAP_TREE1", 580, 0, -200);
	m_tree02.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree02);

	m_tree03.SetPlayerCharacter(L"MAP_TREE1", 580, 0, 200);
	m_tree03.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree03);

	m_tree04.SetPlayerCharacter(L"MAP_TREE1", -190, 0, -630);
	m_tree04.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree04);

	m_tree05.SetPlayerCharacter(L"MAP_TREE1", 190, 0, -630);
	m_tree05.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree05);

	m_tree06.SetPlayerCharacter(L"MAP_TREE1", -630, 0, -200);
	m_tree06.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree06);

	m_tree07.SetPlayerCharacter(L"MAP_TREE1", -630, 0, 200);
	m_tree07.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_tree07);
#pragma endregion

#pragma region MyBarrel
	m_barrel00.SetPlayerCharacter(L"MAP_Barrel", -190, 0, 640);
	m_barrel00.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel00);

	m_barrel01.SetPlayerCharacter(L"MAP_Barrel", -190, 0, 700);
	m_barrel01.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel01);

	m_barrel02.SetPlayerCharacter(L"MAP_Barrel", 190, 0, 640);
	m_barrel02.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel02);

	m_barrel03.SetPlayerCharacter(L"MAP_Barrel", 190, 0, 700);
	m_barrel03.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel03);


	m_barrel10.SetPlayerCharacter(L"MAP_Barrel", -190, 0, -720);
	m_barrel10.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel10);

	m_barrel11.SetPlayerCharacter(L"MAP_Barrel", -190, 0, -780);
	m_barrel11.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel11);

	m_barrel12.SetPlayerCharacter(L"MAP_Barrel", 190, 0, -720);
	m_barrel12.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel12);

	m_barrel13.SetPlayerCharacter(L"MAP_Barrel", 190, 0, -780);
	m_barrel13.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel13);


	m_barrel20.SetPlayerCharacter(L"MAP_Barrel", 670, 0, 200);
	m_barrel20.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel20);

	m_barrel21.SetPlayerCharacter(L"MAP_Barrel", 730, 0, 200);
	m_barrel21.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel21);

	m_barrel22.SetPlayerCharacter(L"MAP_Barrel", 670, 0, -200);
	m_barrel22.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel22);

	m_barrel23.SetPlayerCharacter(L"MAP_Barrel", 730, 0, -200);
	m_barrel23.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel23);

	m_barrel30.SetPlayerCharacter(L"MAP_Barrel", -670, 0, 200);
	m_barrel30.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel30);

	m_barrel31.SetPlayerCharacter(L"MAP_Barrel", -730, 0, 200);
	m_barrel31.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel31);

	m_barrel32.SetPlayerCharacter(L"MAP_Barrel", -670, 0, -200);
	m_barrel32.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel32);

	m_barrel33.SetPlayerCharacter(L"MAP_Barrel", -730, 0, -200);
	m_barrel33.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_barrel33);
#pragma endregion


#pragma region MyFence


	//1시
	m_fence00.SetPlayerCharacter(L"MAP_FENCE", 190, 0, 520);//190 580
	m_fence00.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence00.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence00);
	m_fence01.SetPlayerCharacter(L"MAP_FENCE", 190, 0, 425);
	m_fence01.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence01.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence01);
	m_fence02.SetPlayerCharacter(L"MAP_FENCE", 510, 0, 200);
	m_fence02.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence02.SetRotationY(PI*-0.5);
	m_fence02.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence02);
	m_fence03.SetPlayerCharacter(L"MAP_FENCE", 415, 0, 200);
	m_fence03.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence03.SetRotationY(PI*-0.5);
	m_fence03.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence03);


	m_fence10.SetPlayerCharacter(L"MAP_FENCE", 190, 0, -520);//190 580
	m_fence10.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence10.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence10);
	m_fence11.SetPlayerCharacter(L"MAP_FENCE", 190, 0, -425);
	m_fence11.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence11.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence11);
	m_fence12.SetPlayerCharacter(L"MAP_FENCE", 510, 0, -200);
	m_fence12.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence12.SetRotationY(PI*0.5);
	m_fence12.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence12);
	m_fence13.SetPlayerCharacter(L"MAP_FENCE", 415, 0, -200);
	m_fence13.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence13.SetRotationY(PI*0.5);
	m_fence13.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence13);


	m_fence20.SetPlayerCharacter(L"MAP_FENCE", -190, 0, -520);//190 580
	m_fence20.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence20.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence20);
	m_fence21.SetPlayerCharacter(L"MAP_FENCE", -190, 0, -425);
	m_fence21.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence21.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence21);
	m_fence22.SetPlayerCharacter(L"MAP_FENCE", -510, 0, -200);
	m_fence22.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence22.SetRotationY(PI*0.5);
	m_fence22.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence22);
	m_fence23.SetPlayerCharacter(L"MAP_FENCE", -415, 0, -200);
	m_fence23.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence23.SetRotationY(PI*0.5);
	m_fence23.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence23);


	//11시
	m_fence30.SetPlayerCharacter(L"MAP_FENCE", -190, 0, 520);//190 580
	m_fence30.SetScale(D3DXVECTOR3(2.0f, 1.5f,2.0f));
	m_fence30.SetRotationY(-PI);
	m_fence30.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence30);
	m_fence31.SetPlayerCharacter(L"MAP_FENCE", -190, 0, 425);
	m_fence31.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence31.SetRotationY(-PI);
	m_fence31.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence31);
	m_fence32.SetPlayerCharacter(L"MAP_FENCE", -550, 0, 200);
	m_fence32.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence32.SetRotationY(PI*-0.5);
	m_fence32.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence32);
	m_fence33.SetPlayerCharacter(L"MAP_FENCE", -455, 0, 200);
	m_fence33.SetScale(D3DXVECTOR3(2.0f, 1.5f, 2.0f));
	m_fence33.SetRotationY(PI*-0.5);
	m_fence33.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_fence33);
#pragma endregion

#pragma region MyCarpet

	m_carpet_blacksmith.SetPlayerCharacter(L"MAP_Carpet", 300, 0, 300);
	m_carpet_blacksmith.SetScale(D3DXVECTOR3(4, 4, 4));
	m_carpet_blacksmith.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_carpet_blacksmith);

	m_carpet_church.SetPlayerCharacter(L"MAP_Carpet", -300, 0, 300);
	m_carpet_church.SetScale(D3DXVECTOR3(4, 4, 4));
	m_carpet_church.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_carpet_church);

	m_carpet_windmill.SetPlayerCharacter(L"MAP_Carpet", 300, 0, -300);
	m_carpet_windmill.SetScale(D3DXVECTOR3(4, 4, 4));
	m_carpet_windmill.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_carpet_windmill);
	
	m_carpet_towerRound.SetPlayerCharacter(L"MAP_Carpet", -300, 0, -300);
	m_carpet_towerRound.SetScale(D3DXVECTOR3(4, 4, 4));
	m_carpet_towerRound.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_carpet_towerRound);
#pragma endregion

#pragma region MywagonSack

	m_wagon1.SetPlayerCharacter(L"MAP_Wagon2", 440, 0, 240);	//280
	m_wagon1.SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	m_wagon1.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wagon1);

	m_wagon2.SetPlayerCharacter(L"MAP_Wagon1", 460, 0, -280);	//280
	m_wagon2.SetScale(D3DXVECTOR3(4.0f, 4.0f, 3.0f));
	m_wagon2.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wagon2);

	m_wagon3.SetPlayerCharacter(L"MAP_Wagon1", -460, 0, -280);	//280
	m_wagon3.SetScale(D3DXVECTOR3(4.0f, 4.0f, 3.0f));
	m_wagon3.SetRotationY(-PI);
	m_wagon3.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_wagon3);

	m_Sack00.SetPlayerCharacter(L"MAP_Sack", 240, 0, -430);	
	m_Sack00.SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Sack00.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_Sack00);
	m_Sack01.SetPlayerCharacter(L"MAP_Sack", 280, 0, -430);	
	m_Sack01.SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Sack01.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_Sack01);

	m_Sack10.SetPlayerCharacter(L"MAP_Sack", 240, 0, 400);	
	m_Sack10.SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Sack10.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_Sack10);
	m_Sack11.SetPlayerCharacter(L"MAP_Sack", 280, 0, 400);	
	m_Sack11.SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Sack11.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_Sack11);

	m_Sack20.SetPlayerCharacter(L"MAP_Sack", -240, 0, -400);
	m_Sack20.SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Sack20.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_Sack20);
	m_Sack21.SetPlayerCharacter(L"MAP_Sack", -280, 0, -400);
	m_Sack21.SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Sack21.m_objType = EObjType::AObject;
	ObjectManager::Get().PushObject(&m_Sack21);


#pragma endregion

#pragma region MyOutTree
////
////	m_oTree00.SetPlayerCharacter(L"MAP_TREE1", -1300, 0, 0);	
////	m_oTree00.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree00.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree00);
////
////	m_oTree01.SetPlayerCharacter(L"MAP_TREE1", -1200, 0, 100);	
////	m_oTree01.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree01.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree01);
////
////	m_oTree02.SetPlayerCharacter(L"MAP_TREE1", -1100, 0, 200);	
////	m_oTree02.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree02.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree02);
////
////	m_oTree03.SetPlayerCharacter(L"MAP_TREE1", -1200, 0, -100);	
////	m_oTree03.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree03.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree03);
////
////	m_oTree04.SetPlayerCharacter(L"MAP_TREE1", -1100, 0, -200);	
////	m_oTree04.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree04.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree04);
////
////	m_oTree05.SetPlayerCharacter(L"MAP_TREE1", -1300, 0, 200);	
////	m_oTree05.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree05.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree05);
////
////	m_oTree06.SetPlayerCharacter(L"MAP_TREE1", -1300, 0, -200);	
////	m_oTree06.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree06.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree06);
////
////	m_oTree07.SetPlayerCharacter(L"MAP_TREE1", -1350, 0, -100);	
////	m_oTree07.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree07.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree07);
////
////	m_oTree08.SetPlayerCharacter(L"MAP_TREE1", -1350, 0, 100);	
////	m_oTree08.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree08.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree08);
////
////	m_oTree09.SetPlayerCharacter(L"MAP_TREE1", -1100, 0, 000);	
////	m_oTree09.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree09.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree09);
////
////
////	m_oTree10.SetPlayerCharacter(L"MAP_TREE1", 0, 0, 1300);
////	m_oTree10.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree10.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree10);
////
////	m_oTree11.SetPlayerCharacter(L"MAP_TREE1", 100, 0, 1200);
////	m_oTree11.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree11.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree11);
////
////	m_oTree12.SetPlayerCharacter(L"MAP_TREE1", 200 , 0, 1100);
////	m_oTree12.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree12.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree12);
////
////	m_oTree13.SetPlayerCharacter(L"MAP_TREE1", -100, 0, 1200);
////	m_oTree13.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree13.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree13);
////
////	m_oTree14.SetPlayerCharacter(L"MAP_TREE1",  -200 , 0, 1100);
////	m_oTree14.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree14.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree14);
////
////	m_oTree15.SetPlayerCharacter(L"MAP_TREE1", 200 , 0, 1300);
////	m_oTree15.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree15.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree15);
////
////	m_oTree16.SetPlayerCharacter(L"MAP_TREE1", -200, 0, 1300);
////	m_oTree16.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree16.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree16);
////
////	m_oTree17.SetPlayerCharacter(L"MAP_TREE1", -100, 0, 1350);
////	m_oTree17.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree17.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree17);
////
////	m_oTree18.SetPlayerCharacter(L"MAP_TREE1", 100, 0, 1350);
////	m_oTree18.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree18.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree18);
////
////	m_oTree19.SetPlayerCharacter(L"MAP_TREE1", 0, 0, 1100);
////	m_oTree19.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree19.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree19);
////
////
////	m_oTree20.SetPlayerCharacter(L"MAP_TREE1", 0, 0, -1300);
////	m_oTree20.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree20.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree20);
////
////	m_oTree21.SetPlayerCharacter(L"MAP_TREE1", 100, 0, -1200);
////	m_oTree21.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree21.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree21);
////
////	m_oTree22.SetPlayerCharacter(L"MAP_TREE1", 200, 0, -1100);
////	m_oTree22.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree22.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree22);
////
////	m_oTree23.SetPlayerCharacter(L"MAP_TREE1", -100, 0, -1200);
////	m_oTree23.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree23.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree23);
////
////	m_oTree24.SetPlayerCharacter(L"MAP_TREE1", -200, 0, -1100);
////	m_oTree24.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree24.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree24);
////
////	m_oTree25.SetPlayerCharacter(L"MAP_TREE1", 200, 0, -1300);
////	m_oTree25.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree25.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree25);
////
////	m_oTree26.SetPlayerCharacter(L"MAP_TREE1", -200, 0, -1300);
////	m_oTree26.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree26.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree26);
////
////	m_oTree27.SetPlayerCharacter(L"MAP_TREE1", -100, 0, -1350);
////	m_oTree27.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree27.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree27);
////
////	m_oTree28.SetPlayerCharacter(L"MAP_TREE1", 100, 0, -1350);
////	m_oTree28.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree28.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree28);
////
////	m_oTree29.SetPlayerCharacter(L"MAP_TREE1", 0, 0, -1100);
////	m_oTree29.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree29.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree29);
////
////
////	m_oTree30.SetPlayerCharacter(L"MAP_TREE1", 1300, 0, 0);
////	m_oTree30.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree30.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree30);
////
////	m_oTree31.SetPlayerCharacter(L"MAP_TREE1", 1200, 0, 100);
////	m_oTree31.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree31.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree31);
////
////	m_oTree32.SetPlayerCharacter(L"MAP_TREE1", 1100, 0, 200);
////	m_oTree32.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree32.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree32);
////
////	m_oTree33.SetPlayerCharacter(L"MAP_TREE1", 1200, 0, -100);
////	m_oTree33.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree33.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree33);
////
////	m_oTree34.SetPlayerCharacter(L"MAP_TREE1", 1100, 0, -200);
////	m_oTree34.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree34.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree34);
////
////	m_oTree35.SetPlayerCharacter(L"MAP_TREE1", 1300, 0, 200);
////	m_oTree35.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree35.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree35);
////
////	m_oTree36.SetPlayerCharacter(L"MAP_TREE1", 1300, 0, -200);
////	m_oTree36.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree36.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree36);
////
////	m_oTree37.SetPlayerCharacter(L"MAP_TREE1", 1350, 0, -100);
////	m_oTree37.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree37.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree37);
////
////	m_oTree38.SetPlayerCharacter(L"MAP_TREE1", 1350, 0, 100);
////	m_oTree38.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree38.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree38);
////
////	m_oTree39.SetPlayerCharacter(L"MAP_TREE1", 1100, 0, 0);
////	m_oTree39.SetScale(D3DXVECTOR3(1.3, 0.9, 1.3));
////	m_oTree39.m_objType = EObjType::AObject;
////	ObjectManager::Get().PushObject(&m_oTree39);
#pragma endregion




#pragma region MyBillTree

	auto pPlane = new RPlane(L"T", L"Tree1.png", "VS_Light", "PS_Basic");
	int i = 0;
	m_pTree2D[i] = new GameObject(L"T", pPlane);
	m_pTree2D[i]->SetScale(Vector3::One * 50.0f);
	m_pTree2D[i]->SetPosition(-1000.0f, 180.0f, 0.0f);
	m_pTree2D[i]->SetScale(180.0f, 180.0f, 180.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1100.0f, 180.0f, 50.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1150.0f, 180.0f, 100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1200.0f, 180.0f, 150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1250.0f, 180.0f, 200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1300.0f, 180.0f, 250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1250.0f, 180.0f, -200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1200.0f, 180.0f, -150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1150.0f, 180.0f, -100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1100.0f, 180.0f, -50.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1000.0f, 180.0f, 150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1000.0f, 180.0f, -150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1250.0f, 180.0f, 150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1250.0f, 180.0f, -150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1150.0f, 180.0f, 100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1150.0f, 180.0f, -100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1100.0f, 180.0f, 200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1100.0f, 180.0f, -200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1100.0f, 180.0f, 300.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-1100.0f, 180.0f, -300.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);


	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1000.0f, 180.0f, 0.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1100.0f, 180.0f, 50.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1150.0f, 180.0f, 100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1200.0f, 180.0f, 150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1250.0f, 180.0f, 200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1300.0f, 180.0f, 250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1250.0f, 180.0f, -200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1200.0f, 180.0f, -150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1150.0f, 180.0f, -100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1100.0f, 180.0f, -50.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1000.0f, 180.0f, 150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1000.0f, 180.0f, -150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1250.0f, 180.0f, 150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1250.0f, 180.0f, -150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1150.0f, 180.0f, 100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1150.0f, 180.0f, -100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1100.0f, 180.0f, 200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1100.0f, 180.0f, -200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1100.0f, 180.0f, 300.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(1100.0f, 180.0f, -300.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);



	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(0.0f, 180.0f, 1000.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(50.0f, 180.0f, 1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(100.0f, 180.0f, 1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();

	m_pTree2D[i]->SetPosition(150.0f, 180.0f, 1200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(200.0f, 180.0f, 1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(250.0f, 180.0f, 1300.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-200.0f, 180.0f, 1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-150.0f, 180.0f, 1200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-100.0f, 180.0f, 1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-50.0f, 180.0f, 1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(150.0f, 180.0f, 1000.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-150.0f, 180.0f, 1000.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(150.0f, 180.0f, 1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-150.0f, 180.0f, 1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(100.0f, 180.0f, 1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-100.0f, 180.0f, 1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(200.0f, 180.0f, 1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-200.0f, 180.0f, 1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(300.0f, 180.0f, 1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-300.0f, 180.0f, 1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);

	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(0.0f, 180.0f, -1000.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(50.0f, 180.0f, -1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(100.0f, 180.0f, -1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(150.0f, 180.0f, -1200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(200.0f, 180.0f, -1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(250.0f, 180.0f, -1300.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-200.0f, 180.0f, -1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-150.0f, 180.0f, -1200.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-100.0f, 180.0f, -1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-50.0f, 180.0f, -1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(150.0f, 180.0f, -1000.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-150.0f, 180.0f, -1000.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(150.0f, 180.0f, -1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-150.0f, 180.0f, -1250.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(100.0f, 180.0f, -1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-100.0f, 180.0f, -1150.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(200.0f, 180.0f, -1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-200.0f, 180.0f, -1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(300.0f, 180.0f, -1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
	m_pTree2D[++i] = m_pTree2D[0]->clone();
	m_pTree2D[i]->SetPosition(-300.0f, 180.0f, -1100.0f);
	ObjectManager::Get().PushObject(m_pTree2D[i]);
#pragma endregion


#pragma region SetMatrix

	//m_blacksmith.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_fountain.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_church.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_towerRound.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_windmill.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall00.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall01.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall02.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall03.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall04.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall05.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall10.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall11.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall12.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall13.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall14.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall15.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall20.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall21.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall22.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall23.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall24.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall25.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall30.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall31.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall32.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall33.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall34.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_wall35.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_towerTR.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_towerTL.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_towerBR.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_towerBL.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower0.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower1.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower2.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower3.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower4.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower5.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower6.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_tower7.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house00.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house01.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house02.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house10.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house11.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house12.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house20.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house21.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house22.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house30.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house31.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_house32.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	//m_fence00.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);

#pragma endregion

}

bool MainClass::Init() noexcept
{
	// 폰트 설정
	WriteManager::Get().SetText({ 0, 0 }, L"", D2D1::ColorF::Black, 50, L"Yu Gothic");

	// 씬 설정
	m_curScene = m_SceneList[ESceneName::Intro]	= new IntroScene();
	m_SceneList[ESceneName::Main]	= new GameScene();
	m_SceneList[ESceneName::Lobby] = new LobbyScene();
	
	SetScene(ESceneName::Intro, false);


	
	
	I_CHARMGR.Init();
	if (!I_CHARMGR.Load(DxManager::GetDevice(), DxManager::GetDContext(), L"../../data/Model/CharacterTable.cit")) {
		return false;
	}

	m_Hero.SetPlayerCharacter(Paladin, -100, 0, 0);
	m_Hero.SetScale(D3DXVECTOR3(0.75,0.75,0.75));
	//m_Hero.m_objType = EObjType::AObject;
	//ObjectManager::Get().PushObject(&m_Hero);
	//m_Archer.SetPlayerCharacter(L"Archer", 0, 100, 0);
	//m_zking.SetPlayerCharacter(L"zombie_king", 200, 0, 0);
	//m_EX.SetPlayerCharacter(ZombieEX, -100, 0, 0);
	//m_Mage.SetPlayerCharacter(Mage, 0, -100, 0);
	//m_zr.SetPlayerCharacter(L"zombieR", -200, 0, 0);

	MapInit();




	m_Hero.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);




	return true;
}


bool MainClass::Frame() noexcept
{
	m_curScene->Frame();

	m_Hero.Frame(Timer::SPF, Timer::AccumulateTime);
//	//m_zking.Frame(Timer::SPF, Timer::AccumulateTime);
//	////m_Hero2.Frame(Timer::SPF, Timer::AccumulateTime);
//	//m_EX.Frame(Timer::SPF, Timer::AccumulateTime);
//	//m_Archer.Frame(Timer::SPF, Timer::AccumulateTime);
//	//m_Mage.Frame(Timer::SPF, Timer::AccumulateTime);
//	//m_zr.Frame(Timer::SPF, Timer::AccumulateTime);
	m_pSkyBox->Frame(Timer::SPF, Timer::AccumulateTime);

#pragma region  Action

	//if (Input::GetKeyState(VK_NUMPAD0) == EKeyState::DOWN)
	//{
	//	////	m_bird.Translate(1, 0, 0);
	//	//m_Hero.SetANIM_Loop(Paladin_BLOCK);
	//	////m_Hero2.SetANIM_Loop(Zombie_IDLE);
	//	//m_zking.SetANIM_Loop(Zombie_KING_IDLE);
	//	//m_EX.SetANIM_Loop(ZombieEX_IDLE);

	//	//m_Archer.SetANIM_Loop(Archer_DIVE);
	//	//m_Mage.SetANIM_Loop(Mage_BUFF);
	//	//m_zr.SetANIM_Loop(ZombieR_SHOT);

	//	m_windmill.SetHeroAnimSpeed(10);
	//}
	//if (Input::GetKeyState(VK_NUMPAD1) == EKeyState::DOWN)
	//{
	////	m_bird.Translate(1, 0, 0);
	//	m_Hero.SetANIM_Loop(Paladin_IDLE);
	//	//m_Hero2.SetANIM_Loop(Zombie_IDLE);
	//	m_zking.SetANIM_Loop(Zombie_KING_IDLE);
	//	m_EX.SetANIM_Loop(ZombieEX_IDLE);

	//	m_Archer.SetANIM_Loop(Archer_IDLE);
	//	m_Mage.SetANIM_Loop(Mage_IDLE);
	//	m_zr.SetANIM_Loop(ZombieR_IDLE);
	//}
	////	
	//if (Input::GetKeyState(VK_NUMPAD2) == EKeyState::DOWN)
	//{
	//	m_Hero.SetANIM_Loop(Paladin_WALK);
	//	//m_Hero2.SetANIM_Loop(Zombie_WALK);
	//	m_zking.SetANIM_Loop(Zombie_KING_WALK);
	//	m_EX.SetANIM_Loop(ZombieEX_RUN);

	//	m_Archer.SetANIM_Loop(Archer_WALK);
	//	m_Mage.SetANIM_Loop(Mage_WALK);
	//	m_zr.SetANIM_Loop(ZombieR_WALK);
	//}
	//if (Input::GetKeyState(VK_NUMPAD3) == EKeyState::DOWN)
	//{

	//	m_Hero.SetANIM_Loop(Paladin_BACK);
	////	 m_Hero2.SetANIM_OneTime(Zombie_ATTACK);
	//	m_zking.SetANIM_OneTime(Zombie_KING_ATTACK);
	//	m_EX.SetANIM_OneTime(ZombieEX_ATTACK);
	//	m_Archer.SetANIM_Loop(Archer_BACK);
	//	m_Mage.SetANIM_Loop(Mage_BACK);
	//	m_zr.SetANIM_Loop(ZombieR_ATTACK);
	//}
	//if (Input::GetKeyState(VK_NUMPAD4) == EKeyState::DOWN)
	//{
	////	m_Hero2.SetANIM_Loop(Zombie_CRAWL);
	//	m_Hero.SetANIM_Loop(Paladin_RUN);
	//	m_zking.SetANIM_OneTime(Zombie_KING_JUMP_ATTACK);
	//	m_Archer.SetANIM_Loop(Archer_LEFT);
	//	m_Mage.SetANIM_Loop(Mage_LEFT);
	//	m_zr.SetANIM_Loop(ZombieR_CRAWL);
	//}

	//if (Input::GetKeyState(VK_NUMPAD5) == EKeyState::DOWN)
	//{
	//	//m_Hero2.SetANIM_Loop(Zombie_RUN);
	//	m_Hero.SetANIM_Loop(Paladin_THROW);
	//	m_zking.SetANIM_OneTime(Zombie_KING_ROAR);
	//	m_Archer.SetANIM_Loop(Archer_RIGHT);
	//	m_Mage.SetANIM_Loop(Mage_RIGHT);
	//	m_zr.SetANIM_Loop(ZombieR_RUN);
	//}
	//if (Input::GetKeyState(VK_NUMPAD6) == EKeyState::DOWN)
	//{
	//	//m_Hero2.SetANIM_Loop(Zombie_THROW);
	//	m_Hero.SetANIM_OneTime(Paladin_ATTACK);
	//	m_Archer.SetANIM_Loop(Archer_AIM_IDLE);
	//	m_Mage.SetANIM_Loop(Mage_ATK);
	//}
	//if (Input::GetKeyState(VK_NUMPAD7) == EKeyState::DOWN)
	//{
	//	m_Hero.SetANIM_Loop(Paladin_LEFT);
	//	//m_Hero2.SetANIM_Loop(Zombie_PUNCH);
	//	m_Archer.SetANIM_Loop(Archer_AIM_READY);
	//	m_Mage.SetANIM_Loop(Mage_ATK_DU);
	//}
	//
	//if (Input::GetKeyState(VK_NUMPAD8) == EKeyState::DOWN)
	//{
	//	m_Hero.SetANIM_Loop(Paladin_RIGHT);
	//	//m_Hero2.SetANIM_Loop(L"zombie_dashjump.mat");
	//	m_Archer.SetANIM_Loop(Archer_AIM_SHOT);
	//	m_Mage.SetANIM_Loop(Mage_ATK_UD);
	//}
	//
	//if (Input::GetKeyState(VK_NUMPAD9) == EKeyState::DOWN)
	//{
	//	m_Hero.SetANIM_Loop(Paladin_POWERUP);
	//	m_Archer.SetANIM_Loop(Archer_THROW);
	//	//m_Mage.SetANIM_Loop(Mage_THROW);
	//	m_Mage.SetHeroRender(false);
	//	//int i = I_OBJMGR.LoadObj(DxManager::GetDevice(),
	//	//	 DxManager::GetDContext(),
	//	//	L"../../data/model/TestModel/sword1.skm",
	//	//	L"../../data/model/Character.hlsl");

	//	//AModelObj* fffggg = new AModelObj;
	//	//fffggg->Set(DxManager::GetDevice(), i);

	//	//AModel* const pModel = I_OBJMGR.GetPtr(i);
	//	//ObjWM* pWM = new ObjWM(1);
	//	//pWM->m_pModel = pModel;
	//	//pWM->m_Scene = pModel->m_Scene;
	//	//m_Hero.m_pChar->m_pModelList.push_back(pWM);
	//}
#pragma endregion



	ObjectManager::Get().Frame(Timer::SPF, Timer::AccumulateTime);
	auto rotBill = ObjectManager::Get().CurCamera->GetWorldRotation();
	for (auto& iter : m_pTree2D)
	{
		if (iter == nullptr)
			break;
		iter->SetRotation(0.0f, rotBill.y, 0.0f);
		//iter->UpdateMatrix();
		//iter->Render(pDContext);
	}
	return true;
}

bool MainClass::Render() noexcept
{
	m_curScene->Render();
	m_pSkyBox->Render(DxManager::GetDContext());
	
	//m_Hero.Render(DxManager::GetDContext());
	//m_zking.Render(DxManager::GetDContext());
	////m_Hero2.Render(DxManager::GetDContext());
	//m_EX.Render(DxManager::GetDContext());
	//m_Archer.Render(DxManager::GetDContext());
	//m_Mage.Render(DxManager::GetDContext());
	//m_zr.Render(DxManager::GetDContext());


	DxManager::Get().Render();
	ObjectManager::Get().Render(DxManager::GetDContext());
	m_Hero.Render(DxManager::GetDContext());

	return true;
}

bool MainClass::Release() noexcept
{
	m_curScene->Release();

	return true;
}


void MainClass::SetScene(const ESceneName& sceneName, const bool& useRelease) noexcept
{
	if(useRelease)
		m_curScene->Release();
	m_curScene = m_SceneList[sceneName];
	// 쓰레드 실행
	std::thread initer(&MainClass::Init, m_SceneList[sceneName]);
	initer.detach();
	//// 쓰레드 대기
	//if (initer.joinable())
	//	initer.join();
}









int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,	LPWSTR	  lpCmdLine, int   nCmdShow){
	static MainClass mainWindow;
	mainWindow.SetClientRect(250, 250, 1024, 700);

	if (mainWindow.SetWindow(hInstance, nCmdShow, L"MyGame"))	{
		mainWindow.GameRun();	
	}
	return 0;
	lpCmdLine;	hPrevInstance;
}