#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "miniaudio.h"

void keybindsONG(ma_sound* sound) {
	char buffer[3];

	while (!ma_sound_at_end(sound)) {
		scanf("%s", &buffer);

		if (buffer[0] == 'c') {
			if (ma_sound_is_playing(sound) == 1){
				ma_sound_stop(sound);
			}
			else {
				ma_sound_start(sound);
			}

		}
		else if (buffer[0] == 'r') {
			if (ma_sound_is_looping(sound) == 1) {
				ma_sound_set_looping(sound, 0);
				printf("looping disabled ^_^\n");
			}
			else {
				ma_sound_set_looping(sound, 1);
				printf("looping enabled <3\n");
			}
		}
	}
}

int main(int argc, char** argv) {
	ma_result result;
	ma_engine engine;
	ma_sound sound;

	struct dirent *de;

	char *idx;

	if (argc < 2) {
		fprintf(stderr, "no file path <3\n");
		return 69;
	}

	result = ma_engine_init(NULL, &engine);

	if (result != MA_SUCCESS) {
		return 69;
	}

	DIR *dr = opendir(argv[1]);

	if ((idx = strchr(argv[1], '.')) != NULL) {
		if (!(strcmp(idx, ".mp3") == 1)) {
			ma_sound_init_from_file(&engine, argv[1], 0, NULL, NULL, &sound);
			ma_sound_start(&sound);
			keybindsONG(&sound);
		}
	}
	else {
		if (dr == NULL) {
			fprintf(stderr, "i can't open that, silly <3\n");
			return 69;
		}
		int i = -1;
		while ((de = readdir(dr)) != NULL) {
			i++;

			char fullpath[256];
        	strcpy(fullpath, argv[1]);
        	strcat(fullpath, "/");
        	strcat(fullpath, de->d_name);

			ma_sound_init_from_file(&engine, fullpath, 0, NULL, NULL, &sound);
			ma_sound_start(&sound);
			keybindsONG(&sound);
			ma_sound_uninit(&sound);
		}
	}


	ma_engine_uninit(&engine);
	return 0;
}
