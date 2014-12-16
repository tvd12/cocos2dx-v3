// ===================================================================
//
// Description		
//		Contains the implementation of SFSWebClient
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSWebClient.h"

#include <boost/regex.hpp>

namespace Sfs2X {
namespace Http {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSWebClient::SFSWebClient (boost::asio::io_service& io_service)
	: boostIoService(io_service)
{
	onHttpResponse = boost::shared_ptr<HttpResponseDelegate>();
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSWebClient::~SFSWebClient()
{
}

// -------------------------------------------------------------------
// UploadValuesAsync
// -------------------------------------------------------------------
void SFSWebClient::UploadValuesAsync (boost::shared_ptr<string> uriHost, unsigned short int uriPort, boost::shared_ptr<string> paramName, boost::shared_ptr<string> encodedData)
{
	boost::shared_ptr<TCPClient> client = boost::shared_ptr<TCPClient>();

	try {
		client = boost::shared_ptr<TCPClient>(new TCPClient(boostIoService));

		boost::shared_ptr<IPAddress> address (new IPAddress(IPAddress::IPADDRESSTYPE_IPV4, *uriHost));
		client->SynchConnect(address, uriPort);	
	}
	catch (exception e) {
		boost::shared_ptr<string> messageException (new string(e.what()));
		boost::shared_ptr<string> message (new string("Http error creating http connection: " + (*messageException)));

		OnHttpResponse()->Invoke(true,  message);

		try {
			client->Shutdown();
		}
		catch (exception e) {
			boost::shared_ptr<string> messageException (new string(e.what()));
			boost::shared_ptr<string> message (new string("Error during http scocket shutdown: " + (*messageException)));

			OnHttpResponse()->Invoke(true,  message);
		}

		return;
	}

	try {
		string data = (*paramName) + "=" + (*encodedData);

		boost::shared_ptr<wstring> dataAsNative (new wstring());
		dataAsNative->assign(data.begin(), data.end());

		boost::shared_ptr<string> dataAsUtf8 (new string());
		WStrToUtf8(dataAsNative, dataAsUtf8);

		string sb;
		sb.append("POST /" + (*BBClient::BB_SERVLET) + " HTTP/1.0\r\n");
		sb.append("Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n");

		boost::shared_ptr<string> valueContentLength (new string());
		boost::shared_ptr<string> format (new string ("Content-Length: %ld\r\n"));
		StringFormatter<long int> (valueContentLength, format, dataAsUtf8->size());

		sb.append(*valueContentLength);
		sb.append("\r\n");
		sb.append(data);
		
		boost::shared_ptr<vector<unsigned char> > outputData (new vector<unsigned char>(sb.begin(), sb.end()));
		outputData->push_back('\0');

		client->SynchWrite(outputData);

		string responseFromServer;
		do
		{
			boost::shared_ptr<vector<unsigned char> > receive = client->SynchRead();
			if (receive->size() == 0)
			{
				break;
			}

			boost::shared_ptr<string> src (new string(receive->begin(), receive->end()));
			boost::shared_ptr<wstring> dest (new wstring());
			Utf8toWStr(src, dest);

			responseFromServer.append(dest->begin(), dest->end());

		} while (true);

        // Remove http header and trim whitespaces at the end
		std::vector<string> parts;

		boost::regex re("\\r\\n\\r\\n");
		boost::sregex_token_iterator i(responseFromServer.begin(), responseFromServer.end(), re, -1);
		boost::sregex_token_iterator j;

		while (i != j)
		{
			parts.push_back(*i++);
		}

		if (parts.size() < 2) {
/* [todo]
			OnHttpResponse()->Invoke(true, new string ("Error during http response: connection closed by remote side"));	

			try {
				client->Shutdown();
				delete client;
				client = NULL;
			}
			catch (exception e) {
				string* messageException = new string(e.what());
				string* message = new string("Error during http scocket shutdown: " + (*messageException));
				delete messageException;
				messageException = NULL;

				OnHttpResponse()->Invoke(true,  message);
			}
*/
			return;
		}

		string charsToTrim = " ";
		string dataPayload = parts[1].substr(0, parts[1].find_last_not_of(charsToTrim) + 1);
                
		// Sending to the higher layer
		boost::shared_ptr<string> payload (new string(dataPayload));
		OnHttpResponse()->Invoke(false, payload);
	}
	catch (exception e) {
		boost::shared_ptr<string> messageException (new string(e.what()));
		boost::shared_ptr<string> message (new string("Error during http request: " + (*messageException)));

		OnHttpResponse()->Invoke(true,  message);
	}

	try {
		client->Shutdown();
	}
	catch (exception e) {
		boost::shared_ptr<string> messageException (new string(e.what()));
		boost::shared_ptr<string> message (new string("Error during http scocket shutdown: " + (*messageException)));

		OnHttpResponse()->Invoke(true,  message);
	}
}

// -------------------------------------------------------------------
// OnHttpResponse
// -------------------------------------------------------------------
boost::shared_ptr<HttpResponseDelegate> SFSWebClient::OnHttpResponse ()
{
	return onHttpResponse;
}

// -------------------------------------------------------------------
// OnHttpResponse
// -------------------------------------------------------------------
void SFSWebClient::OnHttpResponse (boost::shared_ptr<HttpResponseDelegate> onHttpResponse)
{
	this->onHttpResponse = onHttpResponse;
}

}	// namespace Http
}	// namespace Sfs2X

