#include "SceneManager.h"

SceneManager*SceneManager::m_SceneManager = NULL;

SceneManager*SceneManager::getInstance()
{
	if (m_SceneManager == NULL)
	{
		m_SceneManager = new SceneManager();
		if (m_SceneManager && m_SceneManager->init())
		{
			m_SceneManager->autorelease();
			m_SceneManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_SceneManager);
			m_SceneManager = NULL;
		}
	}
	return m_SceneManager;
}

bool SceneManager::init()
{
	return true;
}

void SceneManager::changeScene(EnumSceneType enSceneType)
{
	Scene *pScene = NULL;
	switch (enSceneType)
	{
	case en_TollgateSelectScene:
		pScene = TollgateSelectScene::createScene();
		break;
	case en_TollgateScene:
		pScene = TollgateScene::createScene();
		break;
	case en_TollgateEditorScene:
		pScene = TowerPosEditorScene::createScene();
		break;
	case en_WinScene:
		pScene = WinScene::createScene();
		break;
	case en_GameOverScene:
		pScene = GameOver::createScene();
		break;
	default:
		break;
	}
	if (pScene == NULL)
	{
		return;
	}

	Director *pDirector = Director::getInstance();
	Scene* curScene = pDirector->getRunningScene();
	if (curScene == NULL)
	{
		pDirector->runWithScene(pScene);
	}
	else
	{
		pDirector->replaceScene(pScene);
	}
}