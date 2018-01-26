#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
USING_NS_CC;

class TowerPosEditorLayer;
class TowerPosEditorOperateLayer : public Layer {

public:
	TowerPosEditorOperateLayer();
	~TowerPosEditorOperateLayer();

	static TowerPosEditorOperateLayer*create(TowerPosEditorLayer *layer);
	virtual bool init(TowerPosEditorLayer *layer);
	
	virtual void draw(Renderer* renderer, const Mat4& transform, uint32_t flags) override;
private:
	void outputBtnOnClick(Ref *, TouchEventType type);
	void changeModeBtnOnClick(Ref *, TouchEventType type);
	void nextLevelBtnOnClick(Ref *, TouchEventType type);
	void preLevelBtnOnClick(Ref *, TouchEventType type);
	TowerPosEditorLayer *m_editorLayer;
	void onDraw(const Mat4& transform, uint32_t flags);
	CustomCommand _customCommand;
};