/**
* @file TestMain.cpp
* @author Spencer Hoffa
*
* @copyright 2014 Spencer Hoffa
*
* This is a program that will run all unit tests for the XneloUtils library.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2014 Spencer Hoffa
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the
* use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
*		1. The origin of this software must not be misrepresented; you must not
*		claim that you wrote the original software. If you use this software in
*		a product, an acknowledgment in the product documentation would be
*		appreciated but is not required.
*
*		2. Altered source versions must be plainly marked as such, and must not
*		be misrepresented as being the original software.
*
*		3. This notice may not be removed or altered from any source
*		distribution.
*
* This liscense can also be found at: http://opensource.org/licenses/Zlib
*/
#include <iostream>

#include "XneloUtils/Network/Network.hpp"
#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Network/XneloSocket.hpp"

#include "XneloUtils/Logging/Logging.hpp"

#include <vld.h>

int main(int argc, char * argv[])
{
	if (!XNELO::NETWORK::InitializeNetworking())
	{
		std::cout << "Networking not initialized. Some Networking tests will fail." << std::endl;
	}

	XNELO::TESTING::TestMaster * tst = XNELO::TESTING::TestMaster::GetInstance();

	tst->RunAllTest();

	XNELO::NETWORK::ShutdownNetworking();

	return 0;
}
