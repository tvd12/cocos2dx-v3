// ===================================================================
//
// Description		
//		Contains the definition of PacketHeader
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __PacketHeader__
#define __PacketHeader__

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Core {
	
	// -------------------------------------------------------------------
	// Class PacketHeader
	// -------------------------------------------------------------------
	class PacketHeader
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		PacketHeader(bool encrypted, bool compressed, bool blueBoxed, bool bigSized);
		static boost::shared_ptr<PacketHeader> FromBinary(long int headerByte);

		long int ExpectedLength();
		void ExpectedLength(long int value);

		bool Encrypted();
		void Encrypted(bool value);

		bool Compressed();
		void Compressed(bool value);

		bool BlueBoxed();
		void BlueBoxed(bool value);

		bool Binary();
		void Binary(bool value);

		bool BigSized();
		void BigSized(bool value);

		unsigned char Encode();

		boost::shared_ptr<string> ToString();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------

	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		long int expectedLength;
		bool binary;
		bool compressed;
		bool encrypted;
		bool blueBoxed;
		bool bigSized;
	};

}	// namespace Core
}	// namespace Sfs2X

#endif
