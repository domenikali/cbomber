#ifndef ACTION_TESTS_H
#define ACTION_TESTS_H

#include "tests_librarys.hpp"
#include "../src/action.hpp"

/**
 * @brief test the action class
 */

/**
 * @brief test the action constructor
 */
void test_action_constructor();

/**
 * @brief test the action getters and setters
 */

void test_action_setters();

/** 
 * @brief test the action serialization
*/
void test_action_serialize();

/**
 * @brief test action deserialization
 */
void test_action_deserialize();

/**
 * @brief test send and recive action
 */
void test_send_recv_action();



#endif