#include "portaudio/portaudio.h"
#include "link/vlink.h"
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "link/linkpool.h"

class linkAudio
	:public boost::enable_shared_from_this<linkAudio>
	, public vlink
{
public:
	linkAudio(boost::asio::io_service& io_service);
	~linkAudio();
	int start();
	int stop();
	size_t read(char* buf,int len);
	size_t write(const char* buf, int len);
private:
	void lifeSupport();
private:
	boost::asio::io_service* _ios;
	PaStream *stream;
	PaError err;
};

class portAudio {
public:
	static portAudio& instance();
	int getDevices();
	const PaDeviceInfo* getDeviceInfo(int idx);
	int open();
private:
	portAudio();
	~portAudio();
private:
	int err;
};