#include "audio/audio.h"
#include "boost/bind.hpp"
#include <iostream>
#include <fstream>

portAudio & portAudio::instance()
{
	// TODO: 在此处插入 return 语句
	static portAudio pa;
	return pa;
}
int portAudio::getDevices()
{
	return Pa_GetDeviceCount();
}

const PaDeviceInfo * portAudio::getDeviceInfo(int idx)
{
	return Pa_GetDeviceInfo(idx);
}

int portAudio::open()
{
	return 0;
}

portAudio::portAudio() {
	err=Pa_Initialize();
}
portAudio::~portAudio() {
	err=Pa_Terminate();
}

linkAudio::linkAudio(boost::asio::io_service& io_service)
{
	_ios = &io_service;
	intprop["channelCount"] = 2;
	intprop["sampleFormat"] = paInt32;
	intprop["direction"] = 1;
	intprop["sampleRate"] = 44100;
	intprop["framesPerBuffer"] = 1024;
}

linkAudio::~linkAudio()
{
	linkpool::instance().destory(this);
	std::cout << "release linkAudio!!!" << std::endl;
}

int linkAudio::start()
{
	PaStreamParameters streamParameters;
	int direction=intprop["direction"];
	if (-1 == intprop["deviceId"]) {
		streamParameters.device = direction?Pa_GetDefaultInputDevice():Pa_GetDefaultOutputDevice();
	}
	else {
		streamParameters.device = intprop["deviceId"];
	}	
	if (streamParameters.device == paNoDevice) {
		std::cout << "[portAudio]Error message: " << "cannot find input device!!" << std::endl;
		return -3;
	}
	const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(streamParameters.device);
	if (!pInfo) {
		std::cout << "[portAudio]Error message: " << "cannot find input device!!" << std::endl;
		return -3;
	}
	streamParameters.channelCount = intprop["channelCount"];
	streamParameters.sampleFormat = intprop["sampleFormat"];
	streamParameters.suggestedLatency = pInfo->defaultHighInputLatency;
	streamParameters.hostApiSpecificStreamInfo = NULL;
		
	err = Pa_OpenStream(    //打开流
		&stream,
		direction ? &streamParameters : 0,   //如果不需要输入流，则为NULL
		!direction ? &streamParameters : 0,
		intprop["sampleRate"],
		intprop["framesPerBuffer"],
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		NULL, /* no callback, use blocking API */
		NULL); /* no callback, so no callback userData */

	if (paNoError != err) {
		std::cout << "[portAudio]Error message: " << Pa_GetErrorText(err) << std::endl;
		return -1;
	}
	err = Pa_StartStream(stream);
	if (paNoError != err) {
		std::cout << "[portAudio]Error message: " << Pa_GetErrorText(err) << std::endl;
		return -2;
	}
	_ios->post(boost::bind(&linkAudio::lifeSupport, shared_from_this()));
	return 0;
}

int linkAudio::stop()
{
	err = Pa_StopStream(stream);
	if (paNoError != err) {
		std::cout << "[portAudio]Error message: " << Pa_GetErrorText(err) << std::endl;
		return -1;
	}
	return 0;
}

size_t linkAudio::read(char * buf, int len)
{
	int size = len / (intprop["sampleSize"] * intprop["channelCount"]);
	err=Pa_ReadStream(stream,buf,size);
	if (paNoError != err) {
		std::cout << "[portAudio]Error message: " << Pa_GetErrorText(err) << std::endl;
		return -1;
	}
	return 0;
}
size_t linkAudio::write(const char * buf, int len)
{
	int size = len / (intprop["sampleSize"] * intprop["channelCount"]);
	err = Pa_WriteStream(stream, buf, size);
	if (paNoError != err) {
		std::cout << "[portAudio]Error message: " << Pa_GetErrorText(err) << std::endl;
		return -1;
	}
	return 0;
}
void linkAudio::lifeSupport()
{
	
}
