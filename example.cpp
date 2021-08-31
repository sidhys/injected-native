#include "triggerBSOD.hpp"

using namespace triggerBsodNamespace;
using namespace std;

int main() 
{

    cout << "Blue Screen of Death trigger\n";

    system("pause");

    triggerBsod::raiseHardError(); 
    return 0; 
}
