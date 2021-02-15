//
// Created by Ariel Santos on 08/02/21.
//

#include "Robot.h"

void Robot::addCommand(Command cmd) {
  switch (cmd.get_type()) {
    case Command::Move:
    case Command::Collect:
    case Command::Eliminate:
      if (cmd.get_priority()) commands->unshift(cmd);
      else commands->enqueue(cmd);
      break;
    case Command::Activate: activate();
      break;
    case Command::Execute: execute();
      break;
    case Command::Report: report();
      break;
    case Command::Return: endMission();
  }
}

void Robot::resetState() {
  resource_count = 0;
  alien_count = 0;
  pos_x = 0;
  pos_y = 0;
  active = false;
  commands.reset(new Queue<Command>);
  history.reset(new Queue<std::string>);
}

unsigned Robot::get_resource_count() const {
  return resource_count;
}

unsigned Robot::get_alien_count() const {
  return alien_count;
}

void Robot::activate() {
  std::ostringstream msg;

  if (active) msg << "ROBO " << id << " JA ESTA EM MISSAO";
  else {
    msg << "ROBO " << id << " SAIU EM MISSAO";
    active = true;
  }

  basePrint(msg.str());
}

void Robot::execute() {
  if (!active) {
    std::ostringstream msg;
    msg << "ROBO " << id << " NAO ESTA EM MISSAO";
    basePrint(msg.str());
    return;
  }

  while (auto cmd = commands->get_front()) {
    auto data = cmd->get_data();
    switch (data.get_type()) {
      case Command::Move: move(data.get_dest_x(), data.get_dest_y());
        break;
      case Command::Collect: collect();
        break;
      case Command::Eliminate: eliminate();
        break;
      default: break;
    }
    commands->dequeue();
  }
}

void Robot::move(unsigned x, unsigned y) {
  auto point = map->getPoint(x, y);
  std::ostringstream msg;

  if (point == OutOfBounds || point == Obstacle) {
    msg << "IMPOSSIVEL MOVER PARA";
  } else {
    msg << "MOVEU PARA";
    pos_x = x;
    pos_y = y;
  }
  msg << " (" << y << ',' << x << ')';
  history->enqueue(msg.str());
}

void Robot::collect() {
  auto point = map->getPoint(pos_x, pos_y);
  std::ostringstream msg;

  if (point != Resource) {
    msg << "IMPOSSIVEL COLETAR RECURSOS";
  } else {
    msg << "RECURSOS COLETADOS";
    resource_count++;
    map->removePoint(pos_x, pos_y);
  }
  msg << " EM (" << pos_y << ',' << pos_x << ')';
  history->enqueue(msg.str());
}

void Robot::eliminate() {
  auto point = map->getPoint(pos_x, pos_y);
  std::ostringstream msg;

  if (point != Alien) {
    msg << "IMPOSSIVEL ELIMINAR ALIEN";
  } else {
    msg << "ALIEN ELIMINADO";
    alien_count++;
    map->removePoint(pos_x, pos_y);
  }
  msg << " EM (" << pos_y << ',' << pos_x << ')';
  history->enqueue(msg.str());
}

void Robot::report() {
  auto h = history->get_front();
  while (h) {
    robotPrint(h->get_data());
    h = h->get_next();
  }
}

void Robot::endMission() const {
  std::ostringstream msg;
  msg << "ROBO " << id << ' ';
  if (!active) {
    msg << "NAO ESTA EM MISSAO";
  } else {
    msg << "RETORNOU ALIENS " << alien_count << " RECURSOS " << resource_count;
  }
  basePrint(msg.str());
}

void Robot::basePrint(const std::string &msg) {
  std::cout << "BASE: " << msg << std::endl;
}
void Robot::robotPrint(const std::string &msg) const {
  std::cout << "ROBO " << id << ": " << msg << std::endl;
}

