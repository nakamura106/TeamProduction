#ifndef BASESCENE_H_
#define BASESCENE_H_

class BaseScene
{
public:
	BaseScene();
	~BaseScene();
	enum class SceneId
	{
		Title,
		Help,
		Game,
		End,
		Max
	};
	enum class SceneStep
	{
		InitStep,
		MainStep,
		EndStep,
	};
protected:
	SceneId m_CurrentSceneID;

	SceneStep m_CurrentSceneStep;

public:
	virtual void InitScene() {};
	virtual void MainScene() {};
	virtual void EndScene() {};

	virtual SceneId Init();
	virtual SceneId Update();
	virtual void Draw();

};


#endif