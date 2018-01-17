#ifndef __MODULE_AUDIO_FINGERPRINT__
#define __MODULE_AUDIO_FINGERPRINT__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "wav.h"
namespace muses {
	class fingerprint {
	public:
		fingerprint(int frmsize);
		~fingerprint();
		int generate(wav& w,int offset);
	private:
		int _frmSize;
		int _frmHop;
		float* Hamming;
	};
}


#endif // !__MODULE_AUDIO_FINGERPRINT__
