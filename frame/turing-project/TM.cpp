#include "TM.h"

TM::TM(const string filename, bool v_mode)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Failed to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    verbose = v_mode;

    string line;
    while(getline(file, line))
    {
        //skip empty line and line comments
        if(line.empty() || line[0] == ';')
            continue;

        //read states Q
        if(line.find("#Q") == 0)
        {
            size_t start = line.find('{');
            size_t end = line.find('}');
            if(start > end || end == string::npos)
            {
                if(verbose)
                {
                    cerr << "StateInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }

            //handle comment
            size_t comment = line.find(';');
            if(comment < end)
            {
                if(verbose)
                {
                    cerr << "StateInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            for(int i = end + 1; i < comment && i < line.size();i++)
            {
                if(line[i] != ' ')
                {
                    if(verbose)
                    {
                        cerr << "StateInputError: Illegal input";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
            }


            string substr = line.substr(start + 1, end - start - 1);
            stringstream ss(substr);
            string token;
            while(getline(ss, token, ','))
            {
                for(char c : token)
                {
                    //illegal type of state
                    if (!std::isalnum(c) && c != '_') 
                    {
                        if(verbose)
                        {
                            cerr << "StateInputError: state \"" << token << "\" error: The states can only consist of numbers, letters and underline";
                            exit(EXIT_FAILURE);
                        }
                        else
                        {
                            cerr << "syntax error";
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                states.push_back(token);
            }
        }

        //read symbols S
        else if(line.find("#S") == 0)
        {
            size_t start = line.find('{');
            size_t end = line.find('}');
            if(start > end || end == string::npos)
            {
                if(verbose)
                {
                    cerr << "SymbolInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            
            //handle comment
            size_t comment = line.find(';');
            if(comment < end)
            {
                if(verbose)
                {
                    cerr << "SymbolInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            for(int i = end + 1; i < comment && i < line.size();i++)
            {
                if(line[i] != ' ')
                {
                    if(verbose)
                    {
                        cerr << "SymbolInputError: Illegal input";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
            }

            string substr = line.substr(start + 1, end - start - 1);
            stringstream ss(substr);
            string token;
            while(getline(ss, token, ','))
            {
                if(token.size() != 1)
                {
                    if(verbose)
                    {
                        cerr << "SymbolInputError: Symbol cannot be empty or consist of multiple characters";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
                else if(token[0] == ' ' || token[0] == ',' || token[0] == ';' 
                    || token[0] == '{' || token[0] == '}' || token[0] == '*' || token[0] == '_') 
                {
                    if(verbose)
                    {
                        cerr << "SymbolInputError: \'" << token[0] << "\' Symbol cannot be \' \', \',\', \';\', \'{\', \'}\', \'*\' or \'_\'";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
                symbols.push_back(token[0]);
            }
        }

        //read tape symbols G
        else if(line.find("#G") == 0)
        {
            size_t start = line.find('{');
            size_t end = line.find('}');
            if(start > end || end == string::npos)
            {
                if(verbose)
                {
                    cerr << "TapeSymbolInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            
            //handle comment
            size_t comment = line.find(';');
            if(comment < end)
            {
                if(verbose)
                {
                    cerr << "TapeSymbolInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            for(int i = end + 1; i < comment && i < line.size();i++)
            {
                if(line[i] != ' ')
                {
                    if(verbose)
                    {
                        cerr << "TapeSymbolInputError: Illegal input";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
            }

            string substr = line.substr(start + 1, end - start - 1);
            stringstream ss(substr);
            string token;
            while(getline(ss, token, ','))
            {
                if(token.size() != 1)
                {
                    if(verbose)
                    {
                        cerr << "TapeSymbolInputError: Symbol cannot be empty or consist of multiple characters";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }

                else if(token.size() != 1 || token[0] == ' ' || token[0] == ',' || token[0] == ';' 
                    || token[0] == '{' || token[0] == '}' || token[0] == '*') 
                {
                    if(verbose)
                    {
                        cerr << "TapeSymbolInputError: \'" << token[0] << "\' Symbol cannot be \' \', \',\', \';\', \'{\', \'}\' or \'*\'";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
                tape_symbols.push_back(token[0]);
            }

        }
    
        //read start
        else if(line.find("#q0") == 0)
        {
            size_t pos = line.find('=');
            //find '=''s pos
            if(pos != string::npos)
                q0 = line.substr(pos + 1);
            
            //handle comment
            size_t end = line.find(';');
            //find '=''s pos
            if(end != string::npos)
                q0 = q0.substr(0, end);

            //clear space
            auto left = std::find_if(q0.begin(), q0.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            });
            auto right = std::find_if(q0.rbegin(), q0.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base();
            if (left >= right)
            {
                if(verbose)
                {
                    cerr << "StartStateInputError: Start state cannot be empty";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            q0 = string(left, right);

            //q0 should be in states
            if(find(states.begin(), states.end(), q0) == states.end())
            {
                if(verbose)
                {
                    cerr << "StartStateInputError: Start state \"" << q0 << "\" not contained in states";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            cur_state = q0;
        }
    
        //read blank
        else if(line.find("#B") == 0)
        {
            if(line.size() < 6 || line.find("#B = ") != 0)
            {
                if(verbose)
                {
                    cerr << "BlankInputError: illegal blank symbol";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            blank = line[5];
            size_t comment = line.find(';');
            for(int i = 6; i < comment && i < line.size();i++)
            {
                if(line[i] != ' ')
                {
                    if(verbose)
                    {
                        cerr << "TapeSymbolInputError: Illegal input";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
            }

            //blank should be in tape symbols
            if(find(tape_symbols.begin(), tape_symbols.end(), blank) == tape_symbols.end())
            {
                if(verbose)
                {
                    cerr << "BlankInputError: Blank symbol \'" << blank << "\' not contained in tape symbols";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
        }
    
        //read final state
        else if(line.find("#F") == 0)
        {
            size_t start = line.find('{');
            size_t end = line.find('}');
            if(start > end || end == string::npos)
            {
                if(verbose)
                {
                    cerr << "FinalStateInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }

            //handle comment
            size_t comment = line.find(';');
            if(comment < end)
            {
                if(verbose)
                {
                    cerr << "FinalStateInputError: \'{\' and \'}\' unmatchable";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            for(int i = end + 1; i < comment && i < line.size();i++)
            {
                if(line[i] != ' ')
                {
                    if(verbose)
                    {
                        cerr << "FinalStateInputError: Illegal input";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
            }

            string substr = line.substr(start + 1, end - start - 1);
            stringstream ss(substr);
            string token;
            while(getline(ss, token, ','))
            {
                if(find(states.begin(), states.end(), token) == states.end())
                {
                    if(verbose)
                    {
                        cerr << "FinalStateInputError: \'" << token[0] << "\' not contained in states";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
                final_states.push_back(token);
            }
        }

        //read tape num
        else if(line.find("#N") == 0)
        {
            if(line.size() < 6 || line.find("#N = ") != 0)
            {
                if(verbose)
                {
                    cerr << "TapeNumInputError: illegal tape num";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            string num_str = line.substr(5);

            //handle comment
            size_t end = num_str.find(';');
            if(end != string::npos)
                num_str = num_str.substr(0, end);

            //clear space
            auto left = std::find_if(num_str.begin(), num_str.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            });
            auto right = std::find_if(num_str.rbegin(), num_str.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base();
            if (left >= right)
            {
                if(verbose)
                {
                    cerr << "TapeNumInputError: illegal tape num";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            num_str = string(left, right);

            for(char c : num_str)
            {
                if(!isdigit(c))
                {
                    if(verbose)
                    {
                        cerr << "TapeNumInputError: illegal tape num";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }

                }
            }
            tape_num = stoi(num_str);
        }
        
        //read delta
        else
        {
            if(tape_num <= 0)
            {
                if(verbose)
                {
                    cerr << "TapeNumInputError: Tape number hasn't been init";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            
            Transfer trans;

            string str = line;
            stringstream ss(str);
            string token;

            //read old state;
            getline(ss, token, ' ');
            if(find(states.begin(),states.end(),token) == states.end())
            {
                if(verbose)
                {
                    cerr << "TransferInputError: Tranfer state \'" << token << "\' not contained in states";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }

            }
            trans.old_state = token;

            //read old symbol
            getline(ss, token, ' ');
            if(token.size() != tape_num)
            {
                if(verbose)
                {
                    cerr << "TransferInputError: The number of symbols \"" << token << "\" does not match the number of tapes " << tape_num;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            trans.old_symbols = token;

            //read new symbol
            getline(ss, token, ' ');
            if(token.size() != tape_num)
            {
                if(verbose)
                {
                    cerr << "TransferInputError: The number of symbols \"" << token << "\" does not match the number of tapes " << tape_num;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            trans.new_symbols = token;

            //check whether old symbol and new symbol is legal
            for(int i = 0; i < tape_num; i++)
            {
                if(trans.old_symbols[i] != '*' && trans.new_symbols[i] == '*')
                {
                    if(verbose)
                    {
                        cerr << "TransferInputError: illegal transfer from \"" << trans.old_symbols << "\" to \"" << trans.new_symbols << "\"";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }
                }
            }

            //read direction
            getline(ss, token, ' ');
            if(token.size() != tape_num)
            {
                if(verbose)
                {
                    cerr << "TransferInputError: The number of direction symbols \"" << token << "\" does not match the number of tapes: " << tape_num;
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            trans.direction = token;

            //check whether direction symbol is legal
            for(int i = 0; i < tape_num; i++)
            {
                char direction_symbol = trans.direction[i];
                if(direction_symbol != 'r' && direction_symbol != 'l' && direction_symbol != '*')
                {
                    if(verbose)
                    {
                        cerr << "TransferInputError: TThe directional sign can only be \'r\', \'l\' or \'*\' ";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        cerr << "syntax error";
                        exit(EXIT_FAILURE);
                    }

                }
            }

            //read new state
            getline(ss, token, ' ');
            if(find(states.begin(),states.end(),token) == states.end())
            {
                if(verbose)
                {
                    cerr << "TransferInputError: \'" << token << "\' not contained in states";
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cerr << "syntax error";
                    exit(EXIT_FAILURE);
                }
            }
            trans.new_state = token;

            transfers.push_back(trans);
        }
    }
    if(tape_num == -1 || states.empty() || final_states.empty() || symbols.empty() || tape_symbols.empty() || q0.empty() || blank == -1)
    {
        if(verbose)
        {
            cerr << "InitError: The septuple definition is missing or empty";
            exit(EXIT_FAILURE);
        }
    }
}

bool TM::initTape(const string input)
{
    if(verbose)
        cout << "Input: " << input << endl;
    for(int i = 0; i < input.size(); i++)
    {
        char c = input[i];
        //all input char need to be in symbos "S"
        if(find(symbols.begin(), symbols.end(), c) == symbols.end())
        {
            if(verbose)
            {
                cerr << "==================== ERR ====================" << endl;
                cerr << "Symbol \"" << c << "\" in input is not defined in the set of input symbols" << endl;
                cerr << "Input: " << input << endl;
                string spaces = string(7+i, ' ');
                cerr << spaces << '^' << endl;
                cerr << "==================== END ====================";
                std::exit(EXIT_FAILURE);
            }
            else
            {
                cerr << "illegal input string";
                std::exit(EXIT_FAILURE);
            }
            return false;
        }
    }
    //init all tapes
    //first tape
    Tape* first_tape = new Tape(input, blank);
    tapes.push_back(*first_tape);
    //other
    for(int i = 1; i < tape_num; i++)
    {
        Tape* tape = new Tape(blank);
        tapes.push_back(*tape);
    }
    if(verbose)
    {
        cout << "==================== RUN ====================" << endl;
        verbosePrint();
        cur_step++;
    }
    return true;
}

//Judge weather cur_symbols can trans with trans_symbols
bool isValidTrans(string cur_symbols, string trans_symbols, char blank)
{
    for(int i = 0; i < cur_symbols.size(); i++)
    {
        char c_symbol = cur_symbols[i];
        char t_symbol = trans_symbols[i];
        /*
         There're four cases:
         1. c_symbol == t_symbol, match
         2. c_symbol != t_symbol, but t_symbol is '*', which means it can match any symbol(except blank'_'), and c_symbol is not blank, match
         3. c_symbol != t_symbol, t_symbol is '*', but c_symbol is blank, can't match
         4. c_symbol != t_symbol, t_symbol is not '*', can't match
        */
        if((c_symbol != t_symbol && t_symbol != '*') || (c_symbol != t_symbol && t_symbol == '*' && c_symbol == blank))
            return false;
    }
    return true;
}

bool TM::transfer()
{
    string cur_symbols;
    for(int i = 0; i < tape_num; i++)
    {
        cur_symbols.push_back(tapes[i].getCurSymbol());
    }

    //search valid transfer
    bool fail_search = true;
    Transfer valid_trans;
    for(int i = 0; i < transfers.size(); i++)
    {
        if(transfers[i].old_state == cur_state && isValidTrans(cur_symbols, transfers[i].old_symbols, blank) )
        {
            valid_trans = transfers[i];
            fail_search = false;
            break;
        }
    }
    if(fail_search)
        return false;

    //trans each tape
    for(int i = 0; i < tape_num; i++)
    {
        tapes[i].transfer(valid_trans.old_symbols[i], valid_trans.new_symbols[i], valid_trans.direction[i]);
    }

    //trans state
    cur_state = valid_trans.new_state;
    if(find(final_states.begin(),final_states.end(), cur_state) != final_states.end())
        accept = true;
    if(verbose)
    {
        verbosePrint();
    }
    cur_step++;
    return true;
    
}

void TM::printFirstTape()
{
    tapes[0].normalPrint();
}

void TM::verbosePrint()
{
    int space_num = std::to_string(tape_num).size();
    string spaces = string(space_num + 1, ' ');
    cout << "Step " << spaces << ": " << cur_step << endl;
    cout << "State" << spaces << ": " << cur_state << endl;
    cout << "Acc  " << spaces << ": " << (accept ? "Yes" : "No") << endl;

    for(int i = 0; i < tape_num; i++)
    {
        tapes[i].verbosePrint(i, space_num);
    }

    cout << "----------------------------------------------------------------" << endl;

}

//Tape Part
Tape::Tape(const string input, const char blk)
{
    tape = input;
    blank = blk;
    tape.insert(tape.begin(), blank);
    tape.insert(tape.end(), blank);
    zero_position = 1;
    for(pointer = 0; pointer < tape.size(); pointer++)
    {
        if(tape[pointer] != blank)
            break;
    }
}

char Tape::getCurSymbol()
{
    return tape[pointer];
}

void Tape::transfer(char old_symbol, char new_symbol, char direction)
{
    //case1: both old_symbol and new_symbol not '*', change *pointer to new_symbol
    if(old_symbol != '*' && new_symbol != '*')
    {
        assert(old_symbol == tape[pointer]);
        tape[pointer] = new_symbol;
    }
    //case2: old_symbol is '*' but new symbol is not '*'
    else if(old_symbol == '*' && new_symbol != '*')
    {
        tape[pointer] = new_symbol;
    }
    //case3: old_symbol is '*' and new symbol is '*'
    else if(old_symbol == '*' && new_symbol == '*')
    {
        //do nothing;
        ;
    }
    //case4: old_symbol is not '*' but new_symbol is '*', illegal trans, never get here
    else
    {
        assert(0);
    }

    //handle direction;
    if(direction == '*')
    {
        //do nothing
        ;
    }
    else if(direction == 'r')
    {
        if(pointer == tape.size() - 1)
        {
            tape.push_back(blank);
        }
        pointer++;
    }
    else if(direction == 'l')
    {
        if(pointer == 0)
        {
            tape.insert(tape.begin(), blank);
            zero_position++;
        }
        else
        {
            pointer--;
        }
    }
    else
    {
        cerr << "syntax error";
        std::exit(EXIT_FAILURE);        
    }
}

void Tape::normalPrint()
{
    int begin = 0;
    for(;begin < tape.size(); begin++)
    {
        if(tape[begin] != blank)
            break;
    }
    if(begin == tape.size())    return; //the whole tape is empty
    int end = tape.size() - 1;
    for(;end >= begin; end--)
    {
        if(tape[end] != blank)
            break;
    }
    cout << tape.substr(begin, end - begin + 1);
}

//id used for verbose print's id
void Tape::verbosePrint(int id, int max_id_size)
{
    int begin = 0;
    //check:is pointer point to the leftest blank'_'?
    //if true, we need to show the tape from the pointer
    int tmp_begin = begin;
    for(;tape[tmp_begin] == blank && tmp_begin < tape.size(); tmp_begin++);        //move tmp_begin to the first non-blank symbol
    pointer == tmp_begin - 1 ? begin = tmp_begin - 1 : begin = tmp_begin;

    int end = 0;
    //check:is pointer point to the rightest blank'_'?
    //if true. we need to end the tape at the pointer
    int tmp_end = tape.size() - 1;
    for(;tmp_end >= begin && tape[tmp_end] != blank ; tmp_end--);               //Find non-blank symbol from back to front
    pointer == tmp_end ? end = tmp_end : end = tmp_end - 1;

    string out_index;
    string out_tape;
    string out_head;
    for(int i = begin; i <= end; i++)
    {
        int index = getID(i);       //get the id to be print
        /*
         e.g. 
         if index = 15
         then tape need one more space, two space in total
        */
        string tmp_index = std::to_string(index);
        int space_size = tmp_index.size();
        string spaces = string(space_size, ' ');

        out_index += (tmp_index + " ");

        out_tape.push_back(tape[i]);
        out_tape += spaces;

        if(i == pointer)
        {
            out_head.push_back('^');
            out_head += spaces;
        }
        else
        {
            out_head += (" " + spaces);
        }
    }

    int id_size = std::to_string(id).size();
    int space_num = max_id_size - id_size;
    string spaces = string(space_num, ' ');
    if(begin >= tape.size())        //the whole tape is empty
    {
        cout << "Index" << id << spaces << " : " << getID(pointer) << endl;
        cout << "Tape" << id << spaces << "  : " << blank << endl;
        cout << "Head" << id << spaces << "  : " << '^' << endl;
    }
    else
    {
        cout << "Index" << id << spaces << " : " << out_index << endl;
        cout << "Tape" << id << spaces << "  : " << out_tape << endl;
        cout << "Head" << id << spaces << "  : " << out_head << endl;
    }
}

int Tape::getID(int real_id)
{
    return abs(real_id - zero_position);
}