#include "config_tests.hpp"

void test_config_constructor(){
    
    std::cout << "Testing Config constructor... ";
    Config config;
    assert(config.getServerIP6Adress() == "::1");
    assert(config.getServerIP4Adress() == "127.0.0.1");
    assert(config.getServerPort() == 8080);
    ok_message();
}