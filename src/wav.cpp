#include "wav.h"
using namespace muses;
wav::wav() {}
wav::~wav() {}
int wav::open(const char* path) {
	fp = fopen(path, "rb");
	if (fp == NULL) { 
		return -1;
	}
	fread(info.riff_id, 1, 4, fp);
	info.riff_id[4] = '\0';
	fread(&info.size0, 4, 1, fp);
	fread(info.wave_fmt, 1, 8, fp);
	info.wave_fmt[8] = '\0';
	fread(&info.size1, 4, 1, fp);
	fread(&info.fmttag, 2, 1, fp);
	fread(&info.channel, 2, 1, fp);
	fread(&info.sample_per_sec, 4, 1, fp);
	fread(&info.byte_per_sec, 4, 1, fp);
	fread(&info.block_align, 2, 1, fp);
	fread(&info.bit_per_sample, 2, 1, fp);
	if (info.size1 == 0x10) {
		fread(info.data_id, 1, 4, fp);
		info.data_id[4] = '\0';
		fread(&info.size2, 4, 1, fp);
		while (strcmp("DATA", info.data_id) && strcmp("data", info.data_id)) {
			fseek(fp, info.size2, SEEK_CUR);
			fread(info.data_id, 1, 4, fp);
			info.data_id[4] = '\0';
			fread(&info.size2, 4, 1, fp);
		}
	}
	else {
		fseek(fp, 6, SEEK_CUR);
		uint32_t offset;
		fread(&offset, 4, 1, fp);
		fseek(fp, offset, SEEK_CUR);
		fread(info.data_id, 1, 4, fp);
		info.data_id[4] = '\0';
		fread(&info.size2, 4, 1, fp);
	}
	data_offset = info.size0 + 8 - info.size2;

#ifdef WAV_TEST
	printf("=====test file header=====\n");
	printf("riff_id        %-8s 文件头标志\"RIFF\"\n", info.riff_id);
	printf("size0          %-8d 文件总长-8\n", info.size0);
	printf("wave_fmt       %-8s 文件头标志\"WAVEfmt \"\n", info.wave_fmt);
	printf("size1          %-8s 样例文件/标准文件\n", (info.size1 == 0x12) ? "样例文件" : "标准文件");
	printf("fmttag         %-8d \n", info.fmttag);
	printf("channel        %-8d 声道数\n", info.channel);
	printf("sample_per_sec %-8d 采样率\n", info.sample_per_sec);
	printf("byte_per_sec   %-8d 每秒播放字节数\n", info.byte_per_sec);
	printf("block_align    %-8d 采样一次占字节数\n", info.block_align);
	printf("bit_per_sample %-8d 量化数\n", info.bit_per_sample);
	printf("data_id        %-8s \"data\"标志\n", info.data_id);
	printf("size2          %-8d 采样数据字节数\n", info.size2);
	printf("=========================\n");
	printf("播放时长:      %d sec\n", info.size2 / info.byte_per_sec);
#endif
	return 0;
}
int16_t wav::getSample() {
	int16_t s1;
	fread(&s1, 2, 1, fp);
	//FIXME check file end
	return s1;
}
int wav::seek(int offset) {
	return fseek(fp, data_offset + offset, SEEK_SET);
}

wav_info & muses::wav::getInfo()
{
	// TODO: 在此处插入 return 语句
	return info;
}
