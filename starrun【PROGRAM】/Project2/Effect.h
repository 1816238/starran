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
	void Draw();
	const void SetEffectFlag(bool flag);
	const bool GetEffectFlag();
	Effect(Effect& in) {};
	void operator=(Effect&in) {};
private:
	Effect();
	~Effect();
	bool init();
	int effect_image;
	bool effect_flag;
	bool shake_flag;
	int shake_cnt;
};

