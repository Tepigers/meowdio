#include <stdio.h>
#include "miniaudio.h"

int main(int argc, char** argv) {
	ma_result result;
    ma_engine engine;
	ma_sound sound;

	if (argc < 2){
		printf("no file path <3");
		return 69;
	}

    result = ma_engine_init(NULL, &engine);

    if (result != MA_SUCCESS) {
        return 69;
    }
	
	ma_engine_play_sound(&engine, argv[1], &sound);
	ma_sound_set_looping(&sound, 1);

    printf("Press enter to quit...");
    getchar();

    ma_engine_uninit(&engine);
	return 0;
}
