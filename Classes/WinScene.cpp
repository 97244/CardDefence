#include "WinScene.h"
#include "GlobalPath.h"
#include "GlobalParam.h"
#include "SceneManager.h"

Scene* WinScene::createScene() {
	auto scene = Scene::create();

	WinScene* layer = WinScene::create();
	scene->addChild(layer);
	return scene;

	return scene;
}

bool WinScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Label *winLab = Label::create("You Win!", PATH_FONT_PUBLIC, GlobalParam::PublicFontSizeLarge);
	winLab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winLab);

	this->schedule(schedule_selector(WinScene::backToTollgateSelectScene), 3.0f);
	return true;
}

void WinScene::backToTollgateSelectScene(float dt)
{
	SceneManager::getInstance()->changeScene(SceneManager::en_TollgateSelectScene);
}