#include "action_tests.hpp"

void test_action_constructor(){
    std::cout << "Testing action constructor...";
    Header header = Header(1, 1, 1);
    uint16_t number = 1;
    Action action = Action(header, number);
    assert(action.get_header().get_code() == 1);
    assert(action.get_header().get_id() == 1);
    assert(action.get_header().get_team() == 1);
    assert(action.get_action() == 1);
    ok_message();
}

void test_action_setters(){
    std::cout << "Testing action setters...";
    Header header = Header(1, 1, 1);
    uint16_t number = 1;
    Action action = Action(header, number);
    assert(action.get_header().get_code() == 1);
    assert(action.get_header().get_id() == 1);
    assert(action.get_header().get_team() == 1);
    assert(action.get_action() == 1);
    header = Header(2, 0, 0);
    number = 2;
    action.set_header(header);
    action.set_action(number);
    assert(action.get_header().get_code() == 2);
    assert(action.get_header().get_id() == 0);
    assert(action.get_header().get_team() == 0);
    assert(action.get_action() == 2);
    ok_message();
}

void test_action_serialize(){
    std::cout << "Testing action serialization...";
    Header header = Header(1, 1, 1);
    uint16_t number = 1;
    Action action = Action(header, number);
    ssize_t packet_size;
    char * serialized = action.serialize(&packet_size);
    assert(memcmp(serialized, &header, 2) == 0);
    uint16_t temp;
    memcpy(&temp, serialized + 2, 2);
    assert(ntohs(temp)==number);
    ok_message();
}

void test_action_deserialize(){
    std::cout << "Testing action deserialization...";
    Header header = Header(1, 1, 1);
    uint16_t number = 1;
    Action action = Action(header, number);
    ssize_t packet_size;
    char * serialized = action.serialize(&packet_size);
    Action action2 = Action(serialized);
    assert(action2.get_header().get_code() == action.get_header().get_code());
    assert(action2.get_header().get_id() == action.get_header().get_id());
    assert(action2.get_header().get_team() == action.get_header().get_team());
    assert(action2.get_action() == action.get_action());

    ok_message();
}

void test_send_recv_action(){
    std::cout << "Testing send and receive action..."<<std::endl;
    int sock_fd[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, sock_fd);
    Header header = Header(1, 1, 1);
    uint16_t number = 1;
    Action action = Action(header, number);
    action.send_action(sock_fd[0]);
    Action action2 = Action::recv_action(sock_fd[1]);
    assert(action2.get_header().get_code() == action.get_header().get_code());
    assert(action2.get_header().get_id() == action.get_header().get_id());
    assert(action2.get_header().get_team() == action.get_header().get_team());
    assert(action2.get_action() == action.get_action());
    ok_message();
}



