#include <bits/stdc++.h>
using namespace std;

// Opcode Tables
map<string, int> IS = {{"STOP", 0}, {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"MOVER", 4}, {"MOVEM", 5}, {"DIV", 6}, {"READ", 7}, {"PRINT", 8}};
map<string, int> DL = {{"DC", 1}, {"DS", 2}};
map<string, int> AD = {{"START", 1}, {"END", 2}, {"LTORG", 5}};
map<string, int> REG = {{"AREG", 1}, {"BREG", 2}, {"CREG", 3}, {"DREG", 4}};

// Structures
struct Symbol {
    string name;
    int address;
};

struct Literal {
    string value;
    int address;
};

// Tables
vector<Symbol> symtab;
vector<Literal> littab;
vector<int> pooltab = {0};
vector<string> intermediate;

int LC = 0;

// Utility functions
int getSymbolAddress(string name) {
    for (auto &s : symtab)
        if (s.name == name)
            return s.address;
    return -1;
}

int getLiteralAddress(string value) {
    for (auto &l : littab)
        if (l.value == value)
            return l.address;
    return -1;
}

// Pass 1
void pass1(vector<string> code) {
    for (auto line : code) {
        stringstream ss(line);
        string label = "", opcode = "", op1 = "", op2 = "";
        ss >> label;

        // Check if first token is opcode (no label)
        if (IS.count(label) || DL.count(label) || AD.count(label)) {
            opcode = label;
            label = "";
        } else {
            ss >> opcode;
        }

        ss >> op1;
        if (ss >> op2) {} // optional operand 2

        if (opcode == "START") {
            LC = stoi(op1);
            intermediate.push_back("(AD,01) (C," + op1 + ")");
            continue;
        }

        if (!label.empty()) {
            symtab.push_back({label, LC});
        }

        if (IS.count(opcode)) {
            string ic = "(IS," + to_string(IS[opcode]) + ")";
            if (!op1.empty() && REG.count(op1))
                ic += " (R," + to_string(REG[op1]) + ")";
            if (!op2.empty()) {
                if (op2[0] == '=') {
                    littab.push_back({op2, -1});
                    ic += " (L," + to_string(littab.size()) + ")";
                } else {
                    symtab.push_back({op2, -1});
                    ic += " (S," + to_string(symtab.size()) + ")";
                }
            }
            intermediate.push_back(ic);
            LC++;
        }

        else if (DL.count(opcode)) {
            string ic = "(DL," + to_string(DL[opcode]) + ")";
            if (opcode == "DC") {
                ic += " (C," + op1 + ")";
                LC++;
            } else if (opcode == "DS") {
                LC += stoi(op1);
                ic += " (C," + op1 + ")";
            }
            intermediate.push_back(ic);
        }

        else if (opcode == "LTORG") {
            for (int i = pooltab.back(); i < (int)littab.size(); i++) {
                littab[i].address = LC++;
            }
            pooltab.push_back(littab.size());
            intermediate.push_back("(AD,05)");
        }

        else if (opcode == "END") {
            for (int i = pooltab.back(); i < (int)littab.size(); i++) {
                littab[i].address = LC++;
            }
            pooltab.push_back(littab.size());
            intermediate.push_back("(AD,02)");
            break;
        }
    }
}

// Pass 2
void pass2() {
    cout << "\n\n--- MACHINE CODE ---\n";
    int lineNo = 0;
    int currentLC = 0;

    for (auto ic : intermediate) {
        if (ic.find("(IS") != string::npos) {
            stringstream ss(ic);
            string token;
            vector<string> parts;
            while (ss >> token)
                parts.push_back(token);

            int opcode = stoi(parts[0].substr(4, 1));
            int reg = 0, addr = 0;

            if (parts.size() > 1 && parts[1].find("(R,") != string::npos)
                reg = stoi(parts[1].substr(3, 1));

            if (parts.size() > 2) {
                if (parts[2].find("(S,") != string::npos) {
                    int idx = stoi(parts[2].substr(3, 1)) - 1;
                    addr = symtab[idx].address;
                } else if (parts[2].find("(L,") != string::npos) {
                    int idx = stoi(parts[2].substr(3, 1)) - 1;
                    addr = littab[idx].address;
                }
            }

            cout << currentLC++ << " : " << opcode << " " << reg << " " << addr << endl;
        }
    }
}

int main() {
    vector<string> code = {
        "START 200",
        "MOVER AREG,='5'",
        "ADD BREG,ONE",
        "SUB AREG,='1'",
        "MOVEM AREG,TEMP",
        "ONE DC 1",
        "TEMP DS 1",
        "LTORG",
        "END"};

    pass1(code);

    cout << "\n---- INTERMEDIATE CODE ----\n";
    for (auto s : intermediate)
        cout << s << endl;

    cout << "\n---- SYMBOL TABLE ----\n";
    cout << "Index\tSymbol\tAddress\n";
    for (int i = 0; i < (int)symtab.size(); i++)
        cout << i + 1 << "\t" << symtab[i].name << "\t" << symtab[i].address << endl;

    cout << "\n---- LITERAL TABLE ----\n";
    cout << "Index\tLiteral\tAddress\n";
    for (int i = 0; i < (int)littab.size(); i++)
        cout << i + 1 << "\t" << littab[i].value << "\t" << littab[i].address << endl;

    cout << "\n---- POOL TABLE ----\n";
    for (auto p : pooltab)
        cout << p << " ";
    cout << endl;

    pass2();

    return 0;
}
