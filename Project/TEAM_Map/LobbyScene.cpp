#include "LobbyScene.h"



bool LobbyScene::Init() noexcept
{



	return true;
}


// ������
bool LobbyScene::Frame() noexcept
{
	DxManager::Get().Frame();
	ObjectManager::Get().Frame(Timer::SPF, Timer::AccumulateTime);
	SoundManager::Get().Frame();
	return true;
}

// ����
bool LobbyScene::Render() noexcept
{
	DxManager::Get().Render();
	ObjectManager::Get().Render(DxManager::Get().GetDContext());
	SoundManager::Get().Render();
	return true;
}

// ������
bool LobbyScene::Release() noexcept
{
	ObjectManager::Get().Release();
	return true;
}