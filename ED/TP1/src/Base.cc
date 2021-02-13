//
// Created by Ariel Santos on 08/02/21.
//

#include "Base.h"

Base::Base(const std::string &mapfile) : map(new Map(mapfile)) {}

void Base::parseCommands(const std::string &cmdfile) {
  std::string command;
  std::ifstream file(cmdfile);

  while (file >> command) {
    bool priority;
    if (command[0] == '*') {
      priority = true;
      command = command.substr(1);
    } else priority = false;

    unsigned i;
    Robot *robot;
    file >> i;
    if (!robots[i]) {
      robots[i].reset(new Robot(i, map));
      robot = robots[i].get();
    }

    if (command == "MOVER") {
      unsigned x, y;
      std::string rest;
      file >> rest;
      std::sscanf(rest.c_str(), "(%u,%u)", &x, &y); // NOLINT(cert-err34-c)
      robot->addCommand(Command(CmdType::Move, x, y, priority));
    } else if (command == "COLETAR")
      robot->addCommand(Command(CmdType::Collect, priority));
    else if (command == "ELIMINAR")
      robot->addCommand(Command(CmdType::Eliminate, priority));
    else if (command == "ATIVAR")
      robot->addCommand(Command(CmdType::Activate));
    else if (command == "EXECUTAR")
      robot->addCommand(Command(CmdType::Execute));
    else if (command == "RELATORIO")
      robot->addCommand(Command(CmdType::Report));
    else if (command == "RETORNAR") {
      robot->addCommand(Command(CmdType::Return));
      resource_count += robot->get_resource_count();
      alien_count += robot->get_alien_count();
      robot->resetState();
    }
  }
}

void Base::printResult() const {
  std::cout << "BASE: TOTAL ALIENS " << alien_count << " RECURSOS " << resource_count << std::endl;
}

