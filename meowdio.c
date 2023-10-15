#include <stdio.h>
#include "miniaudio.h"
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char** argv) {
	ma_result result;
    ma_engine engine;
	ma_sound sound;

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

	if (argc > 2) {
		ma_sound_set_looping(&sound, 1);
	}

	while (1) {
		fd_set s_rd, s_wr, s_ex;
    	FD_ZERO(&s_rd);
    	FD_ZERO(&s_wr);
    	FD_ZERO(&s_ex);
    	FD_SET(fileno(stdin), &s_rd);
    	select(fileno(stdin)+1, &s_rd, &s_wr, &s_ex, NULL);
	
		char buffer[10];
		read(STDIN_FILENO, buffer, 10);

		if (buffer[0] == 'c') {
			if (ma_sound_is_playing(&sound) == 1){
				ma_sound_stop(&sound);
			}
			else {
				ma_sound_start(&sound);
			}	
			
		}
	}


    printf("Press enter to quit...");
    getchar();

    ma_engine_uninit(&engine);
	return 0;
}
