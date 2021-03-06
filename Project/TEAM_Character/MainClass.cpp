#include "MainClass.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "LobbyScene.h"


GameObject*					MainClass::m_pSkyBox	= nullptr;
map<ESceneName, MainClass*> MainClass::m_SceneList;
MainClass*				    MainClass::m_curScene	= nullptr;



bool MainClass::Init() noexcept
{
	WriteManager::Get().SetText({ 0, 0 }, L"", D2D1::ColorF::Black, 50, L"Yu Gothic");
	m_curScene = m_SceneList[ESceneName::Intro]	= new IntroScene();
	SetScene(ESceneName::Intro, false);
	
	I_CHARMGR.Init();
	if (!I_CHARMGR.Load(DxManager::GetDevice(), DxManager::GetDContext(), L"../../data/Model/CharacterTable.cit")) {
		return false;
	}

	m_Hero.SetPlayerCharacter(Paladin, 0, 0, 200);
	m_Archer.SetPlayerCharacter(Archer, -100, 00, 200);
	m_Mage.SetPlayerCharacter(Mage, 100, 00, 200);
	
	m_zr.SetPlayerCharacter(ZombieR, -100, -100, 200);
	m_EX.SetPlayerCharacter(ZombieEX, 0, -100, 200);
	m_zking.SetPlayerCharacter(Zombie_KING, 100, -100, 200);


	m_Hero.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	m_Archer.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	m_zking.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	m_EX.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	m_Mage.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	m_zr.SetMatrix(0, &ObjectManager::Get().Cameras[ECamera::Main]->m_matView, &ObjectManager::Get().Cameras[ECamera::Main]->m_matProj);
	
	return true;
}


bool MainClass::Frame() noexcept
{
	m_curScene->Frame();

	m_Hero.Frame(Timer::SPF, Timer::AccumulateTime);
	m_zking.Frame(Timer::SPF, Timer::AccumulateTime);
	m_EX.Frame(Timer::SPF, Timer::AccumulateTime);
	m_Archer.Frame(Timer::SPF, Timer::AccumulateTime);
	m_Mage.Frame(Timer::SPF, Timer::AccumulateTime);
	m_zr.Frame(Timer::SPF, Timer::AccumulateTime);

#pragma region  Action

	if (Input::GetKeyState(VK_NUMPAD0) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_BLOCK);
		m_zking.SetANIM_Loop(Zombie_KING_IDLE);
		m_EX.SetANIM_Loop(ZombieEX_IDLE);

		m_Archer.SetANIM_Loop(Archer_DIVE);
		m_Mage.SetANIM_Loop(Mage_BUFF);
		m_zr.SetANIM_Loop(ZombieR_SHOT);

	}
	if (Input::GetKeyState(VK_NUMPAD1) == EKeyState::DOWN)
	{

		m_Hero.SetANIM_Loop(Paladin_IDLE);
		m_zking.SetANIM_Loop(Zombie_KING_IDLE);
		m_EX.SetANIM_Loop(ZombieEX_IDLE);

		m_Archer.SetANIM_Loop(Archer_IDLE);
		m_Mage.SetANIM_Loop(Mage_IDLE);
		m_zr.SetANIM_Loop(ZombieR_IDLE);
	}
	
	if (Input::GetKeyState(VK_NUMPAD2) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_WALK);

		m_zking.SetANIM_Loop(Zombie_KING_WALK);
		m_EX.SetANIM_Loop(ZombieEX_RUN);

		m_Archer.SetANIM_Loop(Archer_WALK);
		m_Mage.SetANIM_Loop(Mage_WALK);
		m_zr.SetANIM_Loop(ZombieR_WALK);
	}
	if (Input::GetKeyState(VK_NUMPAD3) == EKeyState::DOWN)
	{

		m_Hero.SetANIM_Loop(Paladin_BACK);
		m_zking.SetANIM_OneTime(Zombie_KING_ATTACK);
		m_EX.SetANIM_OneTime(ZombieEX_ATTACK);
		m_Archer.SetANIM_Loop(Archer_BACK);
		m_Mage.SetANIM_Loop(Mage_BACK);
		m_zr.SetANIM_Loop(ZombieR_ATTACK);
	}
	if (Input::GetKeyState(VK_NUMPAD4) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_RUN);
		m_zking.SetANIM_OneTime(Zombie_KING_JUMP_ATTACK);
		m_Archer.SetANIM_Loop(Archer_LEFT);
		m_Mage.SetANIM_Loop(Mage_LEFT);
		m_zr.SetANIM_Loop(ZombieR_CRAWL);
	}

	if (Input::GetKeyState(VK_NUMPAD5) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_THROW);
		m_zking.SetANIM_OneTime(Zombie_KING_ROAR);
		m_Archer.SetANIM_Loop(Archer_RIGHT);
		m_Mage.SetANIM_Loop(Mage_RIGHT);
		m_zr.SetANIM_Loop(ZombieR_RUN);
	}
	if (Input::GetKeyState(VK_NUMPAD6) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_OneTime(Paladin_ATTACK);
		m_Archer.SetANIM_Loop(Archer_AIM_IDLE);
		m_Mage.SetANIM_Loop(Mage_ATK);
	}
	if (Input::GetKeyState(VK_NUMPAD7) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_LEFT);
		m_Archer.SetANIM_Loop(Archer_AIM_READY);
		m_Mage.SetANIM_Loop(Mage_ATK_DU);
	}
	
	if (Input::GetKeyState(VK_NUMPAD8) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_RIGHT);
		m_Archer.SetANIM_Loop(Archer_AIM_SHOT);
		m_Mage.SetANIM_Loop(Mage_ATK_UD);
	}
	
	if (Input::GetKeyState(VK_NUMPAD9) == EKeyState::DOWN)
	{
		m_Hero.SetANIM_Loop(Paladin_POWERUP);
		m_Archer.SetANIM_Loop(Archer_THROW);
	}
#pragma endregion

	return true;
}

bool MainClass::Render() noexcept
{
	m_curScene->Render();

	
	m_Hero.Render(DxManager::GetDContext());
	m_zking.Render(DxManager::GetDContext());
	m_Archer.Render(DxManager::GetDContext());
	m_Mage.Render(DxManager::GetDContext());
	m_zr.Render(DxManager::GetDContext());
	m_EX.Render(DxManager::GetDContext());


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