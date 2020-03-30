#ifndef BASESCENE_H_
#define BASESCENE_H_

class BaseScene
{
public:
	BaseScene();
	~BaseScene();

	void Update();
	void Draw();

	SceneId GetCurrentSceneId();
	SceneStep GetCurrentSceneStep();

private:
	enum class SceneId
	{
		Title,
		Help,
		Game,
		End,
	}CurrentSceneID;
	enum class SceneStep
	{
		InitStep,
		MainStep,
		EndStep,
	}CurrentSceneStep;

};


#endif