// ===================================================================
//
// Description		
//		Contains the implementation of BaseController
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "BaseController.h"

namespace Sfs2X {
namespace Bitswarm {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseController::BaseController ()
{
	id = -1;
	sfs = boost::shared_ptr<SmartFox>();
	bitSwarm = boost::shared_ptr<BitSwarmClient>();
	log = boost::shared_ptr<Logger>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
BaseController::BaseController (boost::shared_ptr<BitSwarmClient> bitSwarm)
{
	id = -1;
	sfs = boost::shared_ptr<SmartFox>();
	this->bitSwarm = bitSwarm;
	log = boost::shared_ptr<Logger>();

	if (bitSwarm != NULL)
	{
		log = bitSwarm->Log();
		sfs = bitSwarm->Sfs();
	}
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
BaseController::~BaseController()
{
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
long int BaseController::Id()
{
	return id;
}

// -------------------------------------------------------------------
// Id
// -------------------------------------------------------------------
void BaseController::Id(long int value)
{
	if (id == -1)
	{
		id = value;
	}
	else
	{
		char buffer[512];
		sprintf (buffer, "Controller ID is already set: %ld. Can't be changed at runtime!", id);

		boost::shared_ptr<string> message (new string(buffer));
		boost::shared_ptr<SFSError> exception(new SFSError(message));
		throw exception;
	}
}

}	// namespace Bitswarm
}	// namespace Sfs2X

