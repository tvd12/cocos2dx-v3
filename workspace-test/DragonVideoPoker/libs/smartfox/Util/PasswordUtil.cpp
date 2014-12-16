// ===================================================================
//
// Description		
//		Helper class for logging in with a pre-hashed password
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "PasswordUtil.h"
#include "./md5/md5.h"

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// MD5Password
// -------------------------------------------------------------------
boost::shared_ptr<string> PasswordUtil::MD5Password(string pass)
{
	md5_byte_t digest[16];
	md5_state_t state;
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)pass.c_str(), pass.size());
	md5_finish(&state, digest);
	
	char hex_output[16*2 + 1];
	for (int enumerator = 0; enumerator < 16; ++enumerator)
	{
		sprintf(hex_output + enumerator * 2, "%02x", digest[enumerator]);
	}

	boost::shared_ptr<string> password(new string(hex_output));

	return password;
}


}	// namespace Util
}	// namespace Sfs2X

