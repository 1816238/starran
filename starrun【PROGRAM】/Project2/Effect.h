#pragma once

#define lpEffect Effect::GetInstance()
enum EFFECT_TYPE
{
	SHAKE,
	ROTATION,
	EFFECT_MAX
};

class Effect
{
public:
	static Effect &GetInstance(void)
	{
		static Effect s_Instance;
		return s_Instance;
	}
	void Shake(void);
	void Rotation(void);
	void Draw(EFFECT_TYPE type);
	const void SetEffectFlag(EFFECT_TYPE type,bool flag);
	const bool GetEffectFlag(EFFECT_TYPE type);
	Effect(Effect& in) {};
	void operator=(Effect&in) {};
private:
	Effect();
	~Effect();
	bool init();
	int effect_image[EFFECT_MAX];
	bool effect_flag[EFFECT_MAX];
	bool shake_flag;
	bool escape_flag;
	int shake_cnt;
	float rotation_cnt;
};

