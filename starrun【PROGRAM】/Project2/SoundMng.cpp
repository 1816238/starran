#include"DxLib.h"
#include "SoundMng.h"



const VEC_INT & SoundMng::GetID(std::string f_name)
{
	// map‚É±¸¾½‚µ‚½uŠÔÃŞ°À¶‚ª‚È‚©‚Á‚½‚çƒƒ‚ƒŠ‚ğŠm•Û‚µ‚Ä‚»‚Ì’l‚ğ•Ô‚·
	if (sndMap.find(f_name) == sndMap.end())
	{
		sndMap[f_name].resize(1);
		// imgMap[map][VEC_INT]
		sndMap[f_name][0] = LoadSoundMem((/*"image/" + */f_name/* + ".png"*/).c_str());
		if (sndMap[f_name][0] == -1)
		{
			AST();
		}
	}
	return sndMap[f_name];
}

const int & SoundMng::PlaySound(std::string f_name, int soundType)
{
	return PlaySoundMem(GetID(f_name)[0], soundType);
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}
