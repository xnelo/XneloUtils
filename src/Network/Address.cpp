#include "XneloUtils/Network/Address.hpp"

namespace XNELO
{
	namespace NETWORK
	{
		void Address::SetAddress(XNELO::CORE::uint8 a,
								 XNELO::CORE::uint8 b,
								 XNELO::CORE::uint8 c,
								 XNELO::CORE::uint8 d)
		{
			_address = (a << 24) | (b << 16) | (c << 8) | (d);
			_address = htonl(_address);
		}

		int Address::GetA()
		{
			return _GetAddressPart(24);
		}

		int Address::GetB()
		{
			return _GetAddressPart(16);
		}

		int Address::GetC()
		{
			return _GetAddressPart(8);
		}

		int Address::GetD()
		{
			return _GetAddressPart(0);
		}
	}// end namespace NETWORK
} //end namespace XNELO
