#include <iostream>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    argv[1] = "param1";
    argv[2] = "param2";
    argc = 3;
    std::cout << "Hello world!!!" << std::endl;
    //std::cout << std::getenv("TEST_ENV_VAR") << std::endl;
    std::cout << "printing arguments: " << std::endl;
    for (int i = 0; i < argc; ++i)
    {
        std::string teststring = "a parameter #";
        std::cout << teststring << i << std::endl;
        //std::string my_str = argv[i]; //produces error, because, apparently, c++ string cannot be assigned to c *char value
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
