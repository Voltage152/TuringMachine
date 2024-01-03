#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cassert>

using std::vector;
using std::string;
using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using std::stringstream;

struct Transfer
{
    string old_state;
    string new_state;

    string old_symbols;
    string new_symbols;

    string direction;
};

class Tape
{
private:
    string tape;
    int zero_position;
    int pointer;    //point to a char on the tape
    char blank;
public:
    Tape(const char blk){blank = blk; tape.push_back(blk);pointer = 0;zero_position = 0;};
    Tape(const string input, const char blk);
    char getCurSymbol();
    void transfer(char old_symbol, char new_symbol, char direction);

    void normalPrint();
    void verbosePrint(int id, int max_id_size);    //max_id_size is used to adjust the output format
    int getID(int real_id);
};

class TM
{
private:
    bool accept = false;

    int tape_num = -1;              //N
    vector<Tape> tapes;

    vector<string> states;          //Q
    vector<string> final_states;    //F

    vector<char> symbols;           //S
    vector<char> tape_symbols;      //G

    string q0;                      //q0, should be contained in Q
    string cur_state;

    char blank = -1;                     //B, should be contained in G

    vector<Transfer> transfers;     //delta

    //verbose part
    bool verbose;
    int cur_step = 0;

public:
    TM(const string filename, bool v_mode = false);
    bool initTape(const string input);
    bool transfer();
    bool isAccept(){return accept;};

    //verbose part
    void printFirstTape();
    void verbosePrint();
};
