/*
* ipop-project
* Copyright 2016, University of Florida
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#if defined (_IPOP_LINUX)
#include "lnx_netutils.h"
namespace tincan
{
	namespace linux
	{
		void ParseIP4String(
			const string & src,
			IP4AddressType* out)
		{
			struct sockaddr_in socket_address = { .sin_family = AF_INET,.sin_port = 0 };
			if (inet_pton(AF_INET, src, &socket_address.sin_addr) != 1)
			{
				emsg.append(" - the provided IP4 address could not be resolved.");
				throw TCEXCEPT(emsg.c_str());
			}
			//wrap sockaddr_in struct to sockaddr struct, which is used conventionaly for system calls
			memcpy(&ifr_.ifr_addr, &socket_address, sizeof(struct sockaddr));

			//copies ipv4 address to my my_ipv4. ipv4 address starts at sa_data[2]
			//and terminates at sa_data[5]
			memcpy(ip4_.data(), &ifr_.ifr_addr.sa_data[2], 4);
		}
	} // linux
} // tincan
#endif // _IPOP_LINUX