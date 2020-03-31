#ifndef BASESCENE_H_
#define BASESCENE_H_

class BaseScene
{
public:
	BaseScene();
	~BaseScene();

protected:
	enum class SceneId
	{
		Title,
		Help,
		Game,
		End,
	}m_CurrentSceneID;

	enum class SceneStep
	{
		InitStep,
		MainStep,
		EndStep,
	}m_CurrentSceneStep;

public:
	virtual void InitScene() {};
	virtual void MainScene() {};
	virtual void EndScene() {};

	virtual SceneId Init();
	virtual SceneId Update();
	virtual void Draw();

};


#endif