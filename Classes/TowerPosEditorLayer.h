#pragma once
#include "TowerPos.h"
#include "EnumPosType.h"
class TowerPosEditorLayer :public Layer {
public:
	TowerPosEditorLayer();
	~TowerPosEditorLayer();
	CREATE_FUNC(TowerPosEditorLayer);
	virtual bool init(); 

	/* 把所有坐标对象生成到plist配置文件 */
	void outputPosToPlistFile();

	/* 切换编辑模式 */
	void changeMode();

	/* 切换到下一关卡 */
	int nextLvl();

	/* 切换到上一关卡 */
	int preLvl();
	Vector<PosBase*>getMonsterPosList();
private:
	Vector<PosBase*> m_towerPosList;//存放所有塔防的坐标对象
	int m_iCurLevel;
	void editTowerPos(Point pos);
	PosBase* findExistTowerPos(Point pos);
	void createTowerPos(Point pos);
	void deleteTowerPos(PosBase* existPos);
	void deleteAllPos();
	/* 把指定坐标对象生成到plist配置文件 */
	void outputPosToPlistFile(Vector<PosBase*> posList, const char* sFilePath);
	void loadConfigFile();

	EnumPosType m_enMode;
	void editMonsterPos(Point pos);
	Vector<PosBase*> m_monsterPosList;
	PosBase*findExistMonsterPos(Point pos);
	void createMonsterPos(Point pos);
	void deleteMonsterpos(PosBase*existPos);
	


};