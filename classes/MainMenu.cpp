#include "MainMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto menuTitle =
		MenuItemImage::create("MainMenuScreen/mm_B1.png",
		"MainMenuScreen/mm_B1.png");
	auto playItem =
		MenuItemImage::create("MainMenuScreen/mm_Start.png",
		"MainMenuScreen/mm_Start.png",
		CC_CALLBACK_1(MainMenu::activateGameScene, this));

	auto menu = Menu::create(menuTitle, playItem, NULL);

	// Returns visible size of OpenGL window in points.
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->addChild(menu);

	return true;
}


void MainMenu::activateGameScene(Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}


