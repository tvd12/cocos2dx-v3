// ===================================================================
//
// Description		
//		Contains the implementation of XMLParser
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "XMLParser.h"
#include "XMLNodeValue.h"

namespace Sfs2X {
namespace Util {

char XMLParser::LT			= '<';
char XMLParser::GT			= '>';
char XMLParser::SPACE		= ' ';
char XMLParser::QUOTE		= '"';
char XMLParser::QUOTE2		= '\'';
char XMLParser::SLASH		= '/';
char XMLParser::QMARK		= '?';
char XMLParser::EQUALS		= '=';
char XMLParser::EXCLAMATION = '!';
char XMLParser::DASH        = '-';
//char XMLParser::SQL		= '[';
char XMLParser::SQR			= ']';

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
XMLParser::XMLParser()
{
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
XMLParser::~XMLParser()
{
}

// -------------------------------------------------------------------
// Parse
// -------------------------------------------------------------------
boost::shared_ptr<XMLNode> XMLParser::Parse(boost::shared_ptr<string> content)
{
	boost::shared_ptr<XMLNode> rootNode (new XMLNode());

	tagXMLObject xmlObject;
	xmlObject.type = XMLObjectType_XMLNodeValue;
	xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue("")));
	rootNode->insert(pair<string, tagXMLObject>("_text", xmlObject));

	string nodeContents = "";
		
	bool inElement = false;
	bool collectNodeName = false;
	bool collectAttributeName = false;
	bool collectAttributeValue = false;
	bool quoted = false;
	string attName = "";
	string attValue = "";
	string nodeName = "";
	string textValue = "";
		
	bool inMetaTag = false;
	bool inComment = false;
	bool inCDATA = false;

	boost::shared_ptr<XMLNodeList> parents = (boost::shared_ptr<XMLNodeList>)(new XMLNodeList());
		
	boost::shared_ptr<XMLNode> currentNode = rootNode;

	for (unsigned long int i = 0; i < content->size(); i++)
	{
		char c = content->at(i);
		char cn = '~';  // unused char
		char cnn = '~'; // unused char
		char cp = '~';  // unused char

		if ((i + 1) < content->size()) cn = content->at(i + 1); 
		if ((i + 2) < content->size()) cnn = content->at(i + 2); 
		if (i > 0) cp = content->at(i - 1);

		if (inMetaTag)
		{
			if (c == QMARK && cn == GT)
			{
				inMetaTag = false;
				i++;
			}
				
			continue;
		}
		else
		{
			if (!quoted && c == LT && cn == QMARK)
			{
				inMetaTag = true;
				continue;	
			}	
		}

		if (inComment)
		{
			if (cp == DASH && c == DASH && cn == GT)
			{
				inComment = false;
				i++;
			}

			continue;	
		}
		else
		{
			if (!quoted && c == LT && cn == EXCLAMATION)
			{

				if (content->size() > i + 9 && content->substr(i, 9) == "<![CDATA[")
				{
					inCDATA = true;
					i += 8;
				}
				else
				{					
					inComment = true;
				}

				continue;	
			}
		}

		if (inCDATA)
		{
			if (c == SQR && cn == SQR && cnn == GT)
			{
				inCDATA = false;
				i += 2;
				continue;
			}

			textValue += c;
			continue;	
		}

		if (inElement)
		{
			if (collectNodeName)
			{
				if (c == SPACE)
				{
					collectNodeName = false;
				}
				else if (c == GT)
				{
					collectNodeName = false;
					inElement=false;
				}

				if (!collectNodeName && nodeName.size() > 0)
				{
					if (nodeName[0] == SLASH)
					{
						// close tag
						if (textValue.size() > 0)
						{
							map<string, tagXMLObject>::iterator iterator = currentNode->find("_text");
							if (iterator == currentNode->end())
							{
								tagXMLObject xmlObject;
								xmlObject.type = XMLObjectType_XMLNodeValue;
								xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(textValue)));

								currentNode->insert(pair<string, tagXMLObject>("_text", xmlObject));
							}
							else
							{
								*((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("_text").XMLObjectInstance)) += textValue;
							}
						}

						textValue = "";
						nodeName = "";
						currentNode = parents->Pop();
					}
					else
					{
						if (textValue.size() > 0)
						{
							map<string, tagXMLObject>::iterator iterator = currentNode->find("_text");
							if (iterator == currentNode->end())
							{
								tagXMLObject xmlObject;
								xmlObject.type = XMLObjectType_XMLNodeValue;
								xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(textValue)));

								currentNode->insert(pair<string, tagXMLObject>("_text", xmlObject));
							}
							else
							{
								*((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("_text").XMLObjectInstance)) += textValue;
							}
						}

						textValue = "";	
						boost::shared_ptr<XMLNode> newNode (new XMLNode());

						tagXMLObject xmlObject;
						xmlObject.type = XMLObjectType_XMLNodeValue;
						xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue("")));

						newNode->insert(pair<string, tagXMLObject>("_text", xmlObject));

						tagXMLObject objectName;
						objectName.type = XMLObjectType_XMLNodeValue;
						objectName.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(nodeName)));

						newNode->insert(pair<string, tagXMLObject>("_name", objectName));

						map<string, tagXMLObject>::iterator iterator = currentNode->find(nodeName);
						if (iterator == currentNode->end())
						{
							tagXMLObject xmlObject;
							xmlObject.type = XMLObjectType_XMLNodeList;
							xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeList>)(new XMLNodeList()));

							currentNode->insert(pair<string, tagXMLObject>(nodeName, xmlObject));
						}

						boost::shared_ptr<XMLNodeList> a = (boost::static_pointer_cast<XMLNodeList>)(currentNode->at(nodeName).XMLObjectInstance);
						a->Push(newNode);	
						parents->Push(currentNode);
						currentNode=newNode;
						nodeName="";
					}
				}
				else
				{
					nodeName += c;	
				}
			} 
			else
			{
				if(!quoted && c == SLASH && cn == GT)
				{
					inElement = false;
					collectAttributeName = false;
					collectAttributeValue = false;	
					if (attName.size() > 0)
					{
						if (attValue.size() > 0)
						{
							map<string, tagXMLObject>::iterator iterator = currentNode->find("@" + attName);
							if (iterator == currentNode->end())
							{
								tagXMLObject xmlObject;
								xmlObject.type = XMLObjectType_XMLNodeValue;
								xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(attValue)));

								currentNode->insert(pair<string, tagXMLObject>("@" + attName, xmlObject));
							}
							else
							{
								*((boost::static_pointer_cast<string>)((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("@" + attName).XMLObjectInstance))) = attValue;
							}
						}
						else
						{
							map<string, tagXMLObject>::iterator iterator = currentNode->find("@" + attName);
							if (iterator == currentNode->end())
							{
								tagXMLObject xmlObject;
								xmlObject.type = XMLObjectType_XMLNodeValue;
								xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue("true")));

								currentNode->insert(pair<string, tagXMLObject>("@" + attName, xmlObject));
							}
							else
							{
								*((boost::static_pointer_cast<string>)((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("@" + attName).XMLObjectInstance))) = "true";
							}
						}
					}

					i++;
					currentNode = parents->Pop();
					attName = "";
					attValue = "";		
				}
				else if (!quoted && c == GT)
				{
					inElement = false;
					collectAttributeName = false;
					collectAttributeValue = false;	
					if (attName.size() > 0)
					{
						map<string, tagXMLObject>::iterator iterator = currentNode->find("@" + attName);
						if (iterator == currentNode->end())
						{
							tagXMLObject xmlObject;
							xmlObject.type = XMLObjectType_XMLNodeValue;
							xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(attValue)));

							currentNode->insert(pair<string, tagXMLObject>("@" + attName, xmlObject));
						}
						else
						{
							*((boost::static_pointer_cast<string>)((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("@" + attName).XMLObjectInstance))) = attValue;
						}
					}

					attName = "";
					attValue = "";	
				}
				else
				{
					if (collectAttributeName)
					{
						if (c == SPACE || c == EQUALS)
						{
							collectAttributeName = false;	
							collectAttributeValue = true;
						}
						else
						{
							attName += c;
						}
					}
					else if (collectAttributeValue)
					{
						if (c == QUOTE || c == QUOTE2)
						{
							if (quoted)
							{
								collectAttributeValue = false;

								map<string, tagXMLObject>::iterator iterator = currentNode->find("@" + attName);
								if (iterator == currentNode->end())
								{
									tagXMLObject xmlObject;
									xmlObject.type = XMLObjectType_XMLNodeValue;
									xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(attValue)));

									currentNode->insert(pair<string, tagXMLObject>("@" + attName, xmlObject));
								}
								else
								{
									*((boost::static_pointer_cast<string>)((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("@" + attName).XMLObjectInstance))) = attValue;
								}

								attValue = "";
								attName = "";
								quoted = false;
							}
							else
							{
								quoted = true;	
							}
						}
						else
						{
							if (quoted)
							{
								attValue += c;	
							}
							else
							{
								if (c == SPACE)
								{
									collectAttributeValue = false;	

									map<string, tagXMLObject>::iterator iterator = currentNode->find("@" + attName);
									if (iterator == currentNode->end())
									{
										tagXMLObject xmlObject;
										xmlObject.type = XMLObjectType_XMLNodeValue;
										xmlObject.XMLObjectInstance = (boost::static_pointer_cast<void>)((boost::shared_ptr<XMLNodeValue>)(new XMLNodeValue(attValue)));

										currentNode->insert(pair<string, tagXMLObject>("@" + attName, xmlObject));
									}
									else
									{
										*((boost::static_pointer_cast<string>)((boost::static_pointer_cast<XMLNodeValue>)(currentNode->at("@" + attName).XMLObjectInstance))) = attValue;
									}

									attValue = "";
									attName = "";
								}	
							}
						}
					}
					else if (c == SPACE)
					{

					}
					else
					{
						collectAttributeName = true;							
						attName = "" + c;
						attValue = "";
						quoted = false;		
					}	
				}
			}
		}
		else
		{
			if (c == LT)
			{
				inElement = true;
				collectNodeName = true;	
			}
			else
			{
				textValue += c;	
			}	
		}
	}

	return rootNode;
}

}	// namespace Util
}	// namespace Sfs2X

