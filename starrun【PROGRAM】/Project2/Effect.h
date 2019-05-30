#pragma once

#define lpEffect Effect::GetInstance()

class Effect
{
public:
	static Effect &GetInstance(void)
	{
		static Effect s_Instance;
		return s_Instance;
	}
	void Shake(void);
	//void Draw();
private:
	Effect();
	~Effect();
	bool init();
	int effect_image;
};

