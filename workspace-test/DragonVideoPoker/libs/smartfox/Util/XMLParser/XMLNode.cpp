// ===================================================================
//
// Description		
//		Contains the implementation of XMLNode
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "XMLNode.h"
#include <boost/regex.hpp>				// Boost Asio header

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLNode::XMLNode()
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
XMLNode::~XMLNode()
{
}

// -------------------------------------------------------------------
// GetNodeList
// -------------------------------------------------------------------
boost::shared_ptr<XMLNodeList> XMLNode::GetNodeList(boost::shared_ptr<string> path)
{
	return (boost::static_pointer_cast<XMLNodeList>)(GetObject(path));
}

// -------------------------------------------------------------------
// GetNode
// -------------------------------------------------------------------
boost::shared_ptr<XMLNode> XMLNode::GetNode(boost::shared_ptr<string> path)
{
	return (boost::static_pointer_cast<XMLNode>)(GetObject(path));
}

// -------------------------------------------------------------------
// GetValue
// -------------------------------------------------------------------
boost::shared_ptr<string> XMLNode::GetValue(boost::shared_ptr<string> path)
{
	return (boost::static_pointer_cast<string>)(GetObject(path));
}

// -------------------------------------------------------------------
// GetObject
// -------------------------------------------------------------------
boost::shared_ptr<void> XMLNode::GetObject(boost::shared_ptr<string> path)
{
	std::vector<string> bits;
	boost::shared_ptr<XMLNode> currentNode = shared_from_this();
	boost::shared_ptr<XMLNodeList> currentNodeList = boost::shared_ptr<XMLNodeList>();
	bool listMode = false;
	boost::shared_ptr<void> ob;

	boost::regex re(">");
	boost::sregex_token_iterator i(path->begin(), path->end(), re, -1);
	boost::sregex_token_iterator j;

	while (i != j)
	{
		string tokenizedValue = *i;
		bits.push_back(tokenizedValue.substr(1, tokenizedValue.size() - 1));
		i++;
	}

	for (unsigned long int i = 0; i < bits.size(); i++)
	{
		if (listMode)
        {
			list<boost::shared_ptr<XMLNode> >::iterator iteratorNodeList = currentNodeList->begin();
			std::advance(iteratorNodeList, atoi(bits[i].c_str()));
			currentNode = *iteratorNodeList;
            ob = currentNode;
			listMode = false;
		}
		else
		{
			map<string, tagXMLObject>::iterator iteratorNode = currentNode->find(bits[i]);
			tagXMLObject xmlObject = iteratorNode->second;

			if (xmlObject.type == XMLObjectType_XMLNodeList)
			{
				currentNodeList = (boost::static_pointer_cast<XMLNodeList>)(xmlObject.XMLObjectInstance);
				listMode = true;
			}
			else
			{
				// reached a leaf node/attribute
				if (i != (bits.size() - 1))
				{
					// unexpected leaf node
					string actualPath = "";
					for (unsigned long j = 0; j <= i; j++)
					{
						actualPath = actualPath + ">" + bits[j];
					}
						
					//Debug.Log("xml path search truncated. Wanted: " + path + " got: " + actualPath);
				}
					
				return ob;
			}
		}
	}

	if (listMode) 
		return currentNodeList;
	else 
		return currentNode;
}

}	// namespace Util
}	// namespace Sfs2X

