#include "Root.hpp"
#include "Protocol.hpp"


int main(){
    auto root = Root::getPtr();

    root->Init(1000);

    return root->Run();
}