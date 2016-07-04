/*
 * TinyConfig.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: walter
 */

#include "TinyUtil.h"
#include "TinyConfig.h"
using namespace std;

namespace wfan {

TinyConfig::TinyConfig() {


}

TinyConfig::~TinyConfig() {

}


int TinyConfig::ReadConfigFile(const char* szFilename) {


	ifstream ifile(szFilename);
	if(!ifile)
	{
		LOG_TRACE("Unable to read %s", szFilename);
		return RET_ERR;
	}

	string strLine = "";
	while( getline(ifile,strLine) )
	{
		LOG_TRACE("Read from file: %s" , strLine.c_str());
	}

	ifile.close();


	return RET_OK;

}

void TinyConfig::AddConfigItem(ConfigItemKey key, std::string val) {

}

std::string& TinyConfig::GetConfigItem(ConfigItemKey key) {
	return "";
}

std::string& TinyConfig::GetConfigItem(std::string groupName, std::string keyName) {
	return "";
}

} /* namespace wfan */
