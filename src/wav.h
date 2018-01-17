#ifndef __MODULE_AUDIO_WAV__
#define __MODULE_AUDIO_WAV__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define WAV_TEST
namespace muses {
	struct wav_info {
		char		riff_id[5];
		uint32_t	size0;
		char		wave_fmt[9];
		uint32_t	size1;
		uint16_t	fmttag;
		uint16_t	channel;
		uint32_t	sample_per_sec;
		uint32_t	byte_per_sec;
		uint16_t	block_align;
		uint16_t	bit_per_sample;
		char		data_id[5];
		uint32_t	size2;
	};
	class wav {
	public:
		wav();
		~wav();
		int open(const char* path);
		int16_t getSample();
		int seek(int offset);
		wav_info& getInfo();
	private:
		FILE* fp;
		wav_info info;
		uint32_t data_offset;
	};
}


#endif // !__MODULE_AUDIO_WAV__
