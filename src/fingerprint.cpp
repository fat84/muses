#include "fingerprint.h"
#include <math.h>
#include <iostream>
using namespace muses;
const float PI = 3.1415926;
fingerprint::fingerprint(int frmsize)
	:_frmSize(frmsize),
	_frmHop(frmsize/2){
	Hamming = new float[_frmSize];
	for (int i = 0; i<_frmSize; i++)
		Hamming[i] = (float)(0.54 - 0.46*cos(2 * PI*i / (_frmSize - 1)));
}
fingerprint::~fingerprint() {

}

int fingerprint::generate(wav& w,int offset) {
	wav_info& info = w.getInfo();
	int frame_num = (info.size2 / info.block_align - offset - _frmSize) / _frmHop + 2;
	std::cout << "frame_num:" << frame_num << std::endl;
	w.seek(offset*info.block_align);
	return frame_num;
}