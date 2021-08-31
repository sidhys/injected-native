#include "triggerBSOD.hpp"

using namespace triggerBsodNamespace;

int main() 
{

    std::cout << "Blue Screen of Death trigger\n";

    system("pause");

     triggerBsod::raiseHardError(); 
     return 0; 
}
