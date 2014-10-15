/*
 * TinyServer.cpp
 *
 *  Created on: 2014-6-14
 *      Author: walter
 */

#include <TinyServer.h>

CTinyEchoServer::CTinyEchoServer():m_trptType(TRANSPORT_TCP), m_svcType(SVC_ECHO), m_nPort(0) {
	// TODO Auto-generated constructor stub

}

CTinyEchoServer::~CTinyEchoServer() {
	// TODO Auto-generated destructor stub
}

int CTinyEchoServer::Init(TRANSPORT_PROTOCOL trptType, int nPort)
{
	return 0;
}


void CTinyEchoServer::SetOption(int optionKey, void* optionValue)
{

}

void* CTinyEchoServer::GetOption(int optionKey)
{
	return 0;
}


int CTinyEchoServer::Start()
{
	return 0;
}

int CTinyEchoServer::Run()
{
	return 0;
}

int CTinyEchoServer::Stop()
{
	return 0;
}

int CTinyEchoServer::Clean()
{
	return 0;
}
