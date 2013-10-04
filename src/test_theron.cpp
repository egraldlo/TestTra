/*
 * test_theron.cpp
 *
 *  Created on: 2013-8-4
 *      Author: casa
 */

#include <iostream>
#include <sstream>
using namespace std;

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <Theron/Defines.h>
#include <Theron/Theron.h>

struct TMessage{
	explicit TMessage(const string &message){
		mMessage[0]='\0';
		memcpy(mMessage,message.c_str(),12);
	}
	char mMessage[12];
};

THERON_REGISTER_MESSAGE(TMessage);

class Thandler:public Theron::Actor{
	public:
	Thandler(Theron::Framework &framework, const char *const name)
	:Theron::Actor(framework,name){
		RegisterHandler(this,&Thandler::handler);
	}
	private:
	void handler(const TMessage &message, const Theron::Address from){
		cout<<"get it"<<endl;
	}
};

int test_theron() {
	ostringstream master_ip_port,client_ip_port;

	/*
	 * I have a test on one node, two ports distributed
	 * one is the master,and the other is the client,
	 * definitely you can change the two ports into two ips
	 * to adapt in your PCs.
	 * */
	master_ip_port<<"tcp://"<<"10.11.1.174"<<":5555";
	client_ip_port<<"tcp://"<<"10.11.1.174"<<":5556";
	int m_c=0;
	scanf("%d",&m_c);
	if(m_c==1){
		/*
		 * port 5555 master
		 * */
		Theron::EndPoint masterEndpoint("master",master_ip_port.str().c_str());

		if(!masterEndpoint.Connect(client_ip_port.str().c_str())){
			cout<<"check your network!"<<endl;
		}
		Theron::Framework masterFramework(masterEndpoint);
        sleep(1);
        /*I have a test that shows this "getchar()" is needed,
         * you can have a try. :)
         */
        masterFramework.Send(TMessage("hello"),Theron::Address(),Theron::Address("handler"));
	}else{
		/*
		 * port 5556 client
		 * */
		Theron::EndPoint clientEndpoint("client",client_ip_port.str().c_str());

		if(!clientEndpoint.Connect(master_ip_port.str().c_str())){
			cout<<"check your network!"<<endl;
		}

		Theron::Receiver receiver(clientEndpoint,"clientReceiver");
		Theron::Framework clientFramework(clientEndpoint);
		Thandler handler(clientFramework,"handler");

		receiver.Wait();
	}
	return 0;
}
