//
// Created by alber on 11/11/2022.
//

#include "GameException.h"

GameException::GameException(const std::string &message, std::string file_name, bool fatal)
        : std::runtime_error{message}, fileName{file_name}, fatal{fatal} {
    std::cerr << message << ": " << file_name << std::endl;
}