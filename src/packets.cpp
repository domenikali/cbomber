#include "packets.hpp"



Header::Header(uint16_t code, uint8_t id, uint8_t team){
    head = (code << 3) | (id << 1) | team;
}

uint16_t Header::get_code(){
    return head >> 3;
}

uint8_t Header::get_id(){
    return (head >> 1) & 0b11;
}

uint8_t Header::get_team(){
    return head & 0b1;
}

void Header::decode(uint16_t * code, uint8_t * id, uint8_t * team){
    *code = get_code();
    *id = get_id();
    *team = get_team();
}

void Header::set_code(uint16_t code){
    head = (code << 3) | (head & 0b111);
}

void Header::set_id(uint8_t id){
    head = ((head >> 3) << 3) | (id << 1) | (head & 0b1);
}

void Header::set_team(uint8_t team){
    head = ((head >> 1) << 1) | team;
}

string Header::to_string(){
    return "Header:\ncode: " + std::to_string(get_code()) + " id: " + std::to_string(get_id()) + " team: " + std::to_string(get_team());
}
