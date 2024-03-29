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
    if (type == bus_type::pv) {
      _model._busses.push_back(bus(voltage, 0, name, number, type));
    } else {
      _model._busses.push_back(bus(voltage, 0, name, number, type));

    }
  }
}
void Parser::read_branches(std::ifstream &filestream) {
  std::string string_line;
  auto const regex = std::regex("^\\s*0[\\s\\S]*");
  
  while (std::getline(filestream, string_line) &&
         !std::regex_match(string_line, regex)) {
    _counter++;
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
    _model._lines.push_back(line(_counter, from_bus, to_bus, pf_rect(r, x), vec_admit));
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
    _counter++;
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
    // tab_tf = 0.99;
    // tab_tf = 1 / tab_tf;
    double hs_factor = ((1 - tab_tf) / pow(tab_tf, 2));
    double ls_factor = ((tab_tf - 1) / tab_tf);

    std::vector<pf_rect> vec_admit{
        hs_factor * 1 * (pf_rect(1, 0) / pf_rect(r, x)),
        ls_factor * 1 * (pf_rect(1, 0) / pf_rect(r, x))};
    _model._lines.push_back(
        line(_counter, from_bus, to_bus, tab_tf * pf_rect(r, x), vec_admit));
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
    _model._busses[number - 1]._loads = pf_rect{p, q} / pf_rect{100, 0};
  }
}
void Parser::read_shunts(std::ifstream &filestream) {
  std::string line;
  _model._busses[9]._q += 19.0 / 100;
  _model._busses[23]._q += 4.3 / 100;
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
    if (number != 1) _model._busses[number - 1]._p = power / 100;
  }
}
Parser::~Parser() {}

void Parser::read() {
  std::ifstream filestream("../ieee_30_bus.raw");
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
