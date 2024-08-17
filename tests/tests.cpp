
#include <iostream>
#include "game_tests.hpp"
#include "action_tests.hpp"
#include "config_tests.hpp"
/**
 *   @brief entry point for tests
 * */
int main(){
    std::cout << "Tests started" << std::endl;
    std::cout <<BOLD<< "Testing game class... "<<RESET<<std::endl;
    testReloadConfig();
    std::cout <<BOLD<< "Testing action class... "<<RESET<<std::endl;
    test_action_constructor();
    test_action_setters();
    test_action_serialize();
    test_action_deserialize();
    test_send_recv_action();
    std::cout<<BOLD<< "Testing config class... "<<RESET<<std::endl;
    test_config_constructor();
    std::cout<<GREEN<<"Tests finished"<<RESET<<std::endl;
    return 0;
}

