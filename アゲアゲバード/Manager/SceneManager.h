#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include"../Scene/BaseScene.h"
#include<vector>

class SceneManager
{
public:
	static SceneManager* Instance();

	void Init();

	void Update();
	void Draw();
	void RegisterScene();

	void SetSceneId(BaseScene::SceneId sceneid_);
	void SetSceneStep(BaseScene::SceneStep scenestep_);

	BaseScene::SceneId GetSceneId() { return m_current_scene_id; }
	BaseScene::SceneStep GetSceneStep() { return m_current_scene_step; }

protected:
	SceneManager();
	~SceneManager();

private:
	static SceneManager* p_instance;
	std::vector<BaseScene*> m_Scene;

	BaseScene::SceneId m_current_scene_id=BaseScene::SceneId::Title;
	BaseScene::SceneStep m_current_scene_step;
};


#endif // !SCENEMANAGER_H_
