#include "stdafx.h"
#include "ParseURL.h"

using namespace std;

void InteractWithUser()
{
	int port;
	Protocol protocol;
	string url = "Start";
	string host;
	string document;

	while (!url.empty())
	{

		cout << "Input url: ";
		getline(cin, url);
		cout << endl;

		if (ParseURL(url, protocol, port, host, document))
		{
			cout << url << endl;
			cout << "HOST: " << host << endl;
			cout << "PORT: " << port << endl;
			cout << "DOC: " << document << endl;
		}
		else
		{
			cout << "Invalid url. Please repeat." << endl;
		}
	}

}

int main(int argc, char* argv[])
{
	InteractWithUser();

	return 0;
}