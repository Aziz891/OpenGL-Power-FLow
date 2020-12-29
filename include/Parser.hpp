#include<iostream>
#include<string>
#include "model.hpp"
#include <fstream>



class Parser
{
private:
    /* data */
    std::string _file_path;
    model &_model;
    int _counter =0;
public:
    Parser(model &model);
    ~Parser();
    void read_busses(std::ifstream &filestream );
    void read_loads(std::ifstream &filestream );
    void read_shunts(std::ifstream &filestream );
    void read_generators(std::ifstream &filestream );
    void read_branches(std::ifstream &filestream );
    void read_transformers(std::ifstream &filestream );
    void read();
};
