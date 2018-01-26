#pragma once
#include "TowerPos.h"
#include "EnumPosType.h"
class TowerPosEditorLayer :public Layer {
public:
	TowerPosEditorLayer();
	~TowerPosEditorLayer();
	CREATE_FUNC(TowerPosEditorLayer);
	virtual bool init(); 

	/* ����������������ɵ�plist�����ļ� */
	void outputPosToPlistFile();

	/* �л��༭ģʽ */
	void changeMode();

	/* �л�����һ�ؿ� */
	int nextLvl();

	/* �л�����һ�ؿ� */
	int preLvl();
	Vector<PosBase*>getMonsterPosList();
private:
	Vector<PosBase*> m_towerPosList;//��������������������
	int m_iCurLevel;
	void editTowerPos(Point pos);
	PosBase* findExistTowerPos(Point pos);
	void createTowerPos(Point pos);
	void deleteTowerPos(PosBase* existPos);
	void deleteAllPos();
	/* ��ָ������������ɵ�plist�����ļ� */
	void outputPosToPlistFile(Vector<PosBase*> posList, const char* sFilePath);
	void loadConfigFile();

	EnumPosType m_enMode;
	void editMonsterPos(Point pos);
	Vector<PosBase*> m_monsterPosList;
	PosBase*findExistMonsterPos(Point pos);
	void createMonsterPos(Point pos);
	void deleteMonsterpos(PosBase*existPos);
	


};