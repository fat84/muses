#include "wav.h"
#include "fingerprint.h"
#include <iostream>
int main(int argc,char* argv[]) {
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
	}
	muses::wav wav;
	muses::fingerprint fp(512);
	wav.open(argv[1]);
	fp.generate(wav,0);
	//wav.dump();
	return 0;
}