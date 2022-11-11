//
// Created by alber on 11/11/2022.
//

#ifndef ELABORATO_GAMEEXCEPTION_H
#define ELABORATO_GAMEEXCEPTION_H


#include <stdexcept>
#include <exception>
#include <string>
#include <iostream>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string &message, std::string file_name, bool fatal = false);

private:
    std::string fileName;
    bool fatal;
};


#endif //ELABORATO_GAMEEXCEPTION_H
