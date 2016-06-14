#include "stdafx.h"
#include "OperationsWithShapes.h"

using namespace std;

int main()
{
	vector<shared_ptr<IShape>> shapes;
	cout << "Input shapes name and properties. In the end, enter \"end\"!" << endl;

	COperationsWithShapes handle(cin, cout, shapes);
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!handle.HandleCommand())
		{
			cout << "Wrong Command! Use Help!" << endl;
		}
	}
    return 0;
}

