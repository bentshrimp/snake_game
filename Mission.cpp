//
// Created by user on 6/17/23.
//

#include "Mission.h"

Mission::Mission(int s) : score(s) {}
bool Mission::check(int s) {
    return (score <= s);
}