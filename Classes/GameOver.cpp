#include "GameOver.h"
#include "GlobalPath.h"
#include "GlobalParam.h"
#include "SceneManager.h"

Scene* GameOver::createScene() {
	auto scene = Scene::create();

	GameOver* layer = GameOver::create();
	scene->addChild(layer);
	return scene;

	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Label *gameOverLab = Label::create("GameOver!", PATH_FONT_PUBLIC, GlobalParam::PublicFontSizeLarge);
	gameOverLab->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(gameOverLab);

	this->schedule(schedule_selector(GameOver::backToTollgateSelectScene), 3.0f);
	return true;
}

void GameOver::backToTollgateSelectScene(float dt)
{
	SceneManager::getInstance()->changeScene(SceneManager::en_TollgateSelectScene);
}