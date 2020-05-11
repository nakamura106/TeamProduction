#ifndef BASESCENE_H_
#define BASESCENE_H_

class BaseScene
{
public:
	BaseScene();
	~BaseScene();
	
protected:
	
	

public:
	virtual void InitScene() {};
	virtual void MainScene() {};
	virtual void EndScene() {};

	virtual void Init();
	virtual void Update();
	virtual void Draw();

};


#endif