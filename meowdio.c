#include <stdio.h>
#include "miniaudio.h"

int main(int argc, char** argv) {
	ma_result result;
    ma_engine engine;
	ma_sound sound;

	char buffer[3];
	
	if (argc < 2) {
		printf("no file path <3\n");
		return 69;
	}

    result = ma_engine_init(NULL, &engine);

    if (result != MA_SUCCESS) {
        return 69;
    }
	
	ma_sound_init_from_file(&engine, argv[1], 0, NULL, NULL, &sound);
	ma_sound_start(&sound);

	while (1) {
		scanf("%s", &buffer);

		if (buffer[0] == 'c') {
			if (ma_sound_is_playing(&sound) == 1){
				ma_sound_stop(&sound);
			}
			else {
				ma_sound_start(&sound);
			}	
			
		}
		else if (buffer[0] == 'r') {
			if (ma_sound_is_looping(&sound) == 1) {
				ma_sound_set_looping(&sound, 0);
				printf("looping disabled ^_^\n");
			}
			else {
				ma_sound_set_looping(&sound, 1);
				printf("looping enabled <3\n");
			}
		} 
	}

    ma_engine_uninit(&engine);
	return 0;
}
