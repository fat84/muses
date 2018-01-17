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
	printf("riff_id        %-8s �ļ�ͷ��־\"RIFF\"\n", info.riff_id);
	printf("size0          %-8d �ļ��ܳ�-8\n", info.size0);
	printf("wave_fmt       %-8s �ļ�ͷ��־\"WAVEfmt \"\n", info.wave_fmt);
	printf("size1          %-8s �����ļ�/��׼�ļ�\n", (info.size1 == 0x12) ? "�����ļ�" : "��׼�ļ�");
	printf("fmttag         %-8d \n", info.fmttag);
	printf("channel        %-8d ������\n", info.channel);
	printf("sample_per_sec %-8d ������\n", info.sample_per_sec);
	printf("byte_per_sec   %-8d ÿ�벥���ֽ���\n", info.byte_per_sec);
	printf("block_align    %-8d ����һ��ռ�ֽ���\n", info.block_align);
	printf("bit_per_sample %-8d ������\n", info.bit_per_sample);
	printf("data_id        %-8s \"data\"��־\n", info.data_id);
	printf("size2          %-8d ���������ֽ���\n", info.size2);
	printf("=========================\n");
	printf("����ʱ��:      %d sec\n", info.size2 / info.byte_per_sec);
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
	// TODO: �ڴ˴����� return ���
	return info;
}
