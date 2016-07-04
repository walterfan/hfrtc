/*
 * TinyConfig_test.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: walter
 */

#include "TinyConfig.h"

#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <stdint.h>

using namespace std;
using namespace testing;
using namespace wfan;

using ::testing::Return;
using ::testing::Mock;

class TinyConfigTest: public ::testing::test {
public:
	TinyConfigTest( ) {
		m_pConfig = new TinyConfig();
   }

   void SetUp( ) {
       // code here will execute just before the test ensues
   }

   void TearDown( ) {
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
   }

   ~TinyConfigTest( )  {
       delete m_pConfig;
   }

   // put in any custom data members that you need
   TinyConfig* m_pConfig;
};

TEST_F (TinyConfigTest, UnitTest1) {
{
	int ret = m_pConfig->ReadConfigFile("../etc/hfrtc.ini");

}
