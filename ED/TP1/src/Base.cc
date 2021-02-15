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
    } else { priority = false; }

    unsigned k;
    file >> k;
    if (!robots[k])
      robots[k].reset(new Robot(k, map));

    if (command == "MOVER") {
      unsigned x, y;
      std::string rest;
      file >> rest;
      std::sscanf(rest.c_str(), "(%u,%u)", &y, &x); // NOLINT(cert-err34-c)
      robots[k]->addCommand(Command(Command::Move, x, y, priority));
    } else if (command == "COLETAR") {
      robots[k]->addCommand(Command(Command::Collect, priority));
    } else if (command == "ELIMINAR") {
      robots[k]->addCommand(Command(Command::Eliminate, priority));
    } else if (command == "ATIVAR") {
      robots[k]->addCommand(Command(Command::Activate));
    } else if (command == "EXECUTAR") {
      robots[k]->addCommand(Command(Command::Execute));
    } else if (command == "RELATORIO") {
      robots[k]->addCommand(Command(Command::Report));
    } else if (command == "RETORNAR") {
      robots[k]->addCommand(Command(Command::Return));
      resource_count += robots[k]->get_resource_count();
      alien_count += robots[k]->get_alien_count();
      robots[k]->resetState();
    }
  }
}

void Base::printResult() const {
  std::cout << "BASE: TOTAL DE ALIENS " << alien_count << " RECURSOS " << resource_count << std::flush;
}

