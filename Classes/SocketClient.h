#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__
#include "cocos2d.h"
#include "network/SocketIO.h"
USING_NS_CC;
using namespace cocos2d::network;

//�̳�SocketIO::SIODelegate��ʵ���ĸ��麯��
class SocketClient : public cocos2d::Layer, SocketIO::SIODelegate
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
//	static cocos2d::Scene* createScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//socket����ʱ����
	void onConnect(SIOClient* client);
	//�յ�����ʱ����
	void onMessage(SIOClient* client, const std::string& data);
	//���Ӵ������յ������ź�ʱ����
	void onError(SIOClient* client, const std::string& data);
	//socket�ر�ʱ����
	void onClose(SIOClient* client);

	// implement the "static create()" method manually
	CREATE_FUNC(SocketClient);

	SIOClient *client;

};

#endif // __TestSocketIo_SCENE_H__
