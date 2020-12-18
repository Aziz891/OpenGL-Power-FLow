#include "Parser.hpp"

#include <regex>

#include "bus.hpp"

Parser::Parser(model &model) : _model(model) {}
void Parser::read_busses(std::ifstream &filestream) {
  std::string line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  while (std::getline(filestream, line) && !std::regex_match(line, regex)) {
    std::istringstream stream(line);
    std::string value;
    size_t counter = 0;
    bus_type type;
    std::string name;
    int number;
    double voltage = 0;
    while (std::getline(stream, value, ',')) {
      switch (counter) {
        case 0:
          number = std::stoi(value);
          break;
        case 1:
          name = value;
          break;
        case 3:
          type = (bus_type)(std::stoi(value) - 1);
          break;
        case 7:
          voltage = std::stod(value);
          break;

        default:
          break;
      }
      counter++;
    }
    // std::cout << line << std::endl;
    _model._busses.push_back(bus(voltage, 0, name, number, type));
  }
}
void Parser::read_branches(std::ifstream &filestream) {
  std::string string_line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  while (std::getline(filestream, string_line) &&
         !std::regex_match(string_line, regex)) {
    std::istringstream stream(string_line);
    std::string value;
    size_t counter = 0;
    std::string name;
    int from_bus;
    int to_bus;
    double r, x, half_b;
    while (std::getline(stream, value, ',')) {
      switch (counter) {
        case 0:
          from_bus = std::stoi(value) - 1;
          break;
        case 1:
          to_bus = std::stoi(value) - 1;
          break;
        case 3:
          r = std::stod(value);
          break;
        case 4:
          x = std::stod(value);
          break;
        case 5:
          half_b = std::stod(value);
          break;

        default:
          break;
      }
      counter++;
    }
    // std::cout << string_line << std::endl;
    std::vector<pf_rect> vec_admit(2, pf_rect(0, half_b));
    _model._lines.push_back(line(from_bus, to_bus, pf_rect(r, x), vec_admit));
    // _model._lines.push_back(
    //     line(from_bus, to_bus, pf_rect{r, x}, pf_rect{0, half_b}
    //     )
    //     );
  }
}
void Parser::read_transformers(std::ifstream &filestream) {
  std::string string_line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  while (std::getline(filestream, string_line) &&
         !std::regex_match(string_line, regex)) {
    std::string value;
    size_t counter = 0;
    size_t counter2 = 0;
    std::string name;
    int from_bus;
    int to_bus;
    double r, x, tab_tf;
    do {
      std::istringstream stream(string_line);
      while (std::getline(stream, value, ',')) {
        switch (counter) {
          case 0:
            from_bus = std::stoi(value) - 1;
            break;
          case 1:
            to_bus = std::stoi(value) - 1;
            break;
          case 20:
            r = std::stod(value);
            break;
          case 21:
            x = std::stod(value);
            break;
          case 23:
            tab_tf = std::stod(value);
            break;

          default:
            break;
        }
        counter++;
      }
      counter2++;
    } while (counter2 < 4 && std::getline(filestream, string_line));
    // std::cout << string_line << std::endl;
    const double hs_factor = (pow(tab_tf, 2) / (1 - tab_tf));
    const double ls_factor = (tab_tf / (tab_tf - 1));

    std::vector<pf_rect> vec_admit{hs_factor * pf_rect(0, tab_tf),
                                   ls_factor * pf_rect(0, tab_tf)};
    _model._lines.push_back(
        line(from_bus, to_bus, tab_tf * pf_rect(r, x), vec_admit));
  }
}
void Parser::read_loads(std::ifstream &filestream) {
  std::string line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  while (std::getline(filestream, line) && !std::regex_match(line, regex)) {
    std::istringstream stream(line);
    std::string value;
    size_t counter = 0;
    int number;
    double p = 0;
    double q = 0;
    while (std::getline(stream, value, ',')) {
      switch (counter) {
        case 0:
          number = std::stoi(value);
          break;
        case 5:
          p = std::stod(value);
          break;
        case 6:
          q = std::stod(value);
          break;

        default:
          break;
      }
      counter++;
    }
    // std::cout << line << std::endl;
    _model._busses[number - 1]._loads = pf_rect{p, q};
  }
}
void Parser::read_shunts(std::ifstream &filestream) {
  std::string line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  while (std::getline(filestream, line) && !std::regex_match(line, regex)) {
    // std::istringstream stream(line);
    // std::string value;
    // size_t counter = 0;
    // bus_type type;
    // std::string name;
    // int number;
    // double voltage = 0;
    // while (std::getline(stream, value, ',')) {
    //   switch (counter) {
    //     case 0:
    //       number = std::stoi(value);
    //       break;
    //     case 1:
    //       name = value;
    //       break;
    //     case 3:
    //       type = (bus_type)(std::stoi(value) -1 ) ;
    //       break;
    //     case 7:
    //       voltage = std::stod(value);
    //       break;

    //     default:
    //       break;
    //   }
    //   counter++;
    // }
    // std::cout << line << std::endl;
    // _model._busses.push_back(bus(voltage, 0, name, number, type ));
  }
}
void Parser::read_generators(std::ifstream &filestream) {
  std::string line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  while (std::getline(filestream, line) && !std::regex_match(line, regex)) {
    std::istringstream stream(line);
    std::string value;
    size_t counter = 0;
    int number;
    double power = 0;
    while (std::getline(stream, value, ',')) {
      switch (counter) {
        case 0:
          number = std::stoi(value);
          break;
        case 2:
          power = std::stod(value);
          break;

        default:
          break;
      }
      counter++;
    }
    // std::cout << line << std::endl;
    if (number != 1) _model._busses[number - 1]._p = power;
  }
}
Parser::~Parser() {}

void Parser::read() {
  std::ifstream filestream("../IEEE 30 bus.RAW");
  std::string line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  std::getline(filestream, line);
  std::getline(filestream, line);
  std::getline(filestream, line);
  if (filestream.is_open()) {
    read_busses(filestream);
    read_loads(filestream);
    read_shunts(filestream);
    read_generators(filestream);
    read_branches(filestream);
    read_transformers(filestream);
    std::cout << "";
  }
}
