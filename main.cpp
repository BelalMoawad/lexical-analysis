#include <bits/stdc++.h>
#include <regex>
#include<time.h>
#include <iterator>
#include<windows.h>
#define deb(x) cout<<#x<<" = "<<x<<endl

using namespace std;

map<string,string> Make_Regex_Map(){
    map<string,string> my_map {
            { "\\;|\\{|\\}|\\(|\\)|\\,|\\#", "Special Symbol"},
            { "int|char|float|bool|cin|cout|main|using|namespace|std","Keywords"},
            { "\\include|define", "Pre-Processor Directive"},
            {"\\iostream|\\stdio|\\string","Library"},
            { "\\*|\\+|\\>>|\\<<|<|>",  "operationerator"},
            { "[0-9]+" ,   "Integer" },
            { "[^include][^iostream][^int][^main][^cin][^cout][^;][^>>][^,][^[B ;cin]][a-z]+" ,   "Identifier" },
            { "[A-Z]+",    "Variable"},
            {"[ ]",""},
    };
    return my_map;
}

map<size_t,pair<string,string>> Find_tokening_results (map<string,string> Language_Rules,string sourceFile) {

    map <size_t, pair<string, string>> res;

    for (auto i = Language_Rules.begin(); i != Language_Rules.end(); ++i) {
        regex compare(i->first);
        auto words_begin = sregex_iterator(sourceFile.begin(), sourceFile.end(), compare);
        auto words_end = sregex_iterator();
        for (auto it = words_begin; it != words_end; ++it)
            res[it->position()] = make_pair(it->str(), i->second);
    }
    return res;
}



map<string, string> Convert(){
    map<string, string> res;
    res["*"] =  "MUL";
    res["+"] =  "ADD";
    res[">>"] =  "RSHFT";
    res["<<"] =  "LSHFT";
    res[">"] =  "GREATER";
    res["<"] =  "LESS";
    return res;
}
int main()
{
    ofstream fout;
    cout.fill(' ');
    cout.width(100);
    fout.open("OutputFile");
    char c;

    fstream fin("MySourceCode.txt", fstream::in);
    string str;
    if(fin.is_open()){
        while(fin>> noskipws>>c)
            str += c;

        map<string,string> Language_Rules =Make_Regex_Map();

        map<string, string> convert = Convert();

        map< size_t, pair<string,string> > ret = Find_tokening_results(Language_Rules,str);


        int count = 1;
        cout<<"\t\t\t\t-------------------------------------------------------------------------------------------------- \n";
        cout.width(40);
        cout<<"\t        NUMBER"<<setw(10)<<"              TOKEN "<< " "<< "            "<<setw(20)<<" PATTERN \n";
        cout.fill(' ');
        cout.width(40);

        cout<<"\t\t\t\t-------------------------------------------------------------------------------------------------- \n\n\n";



        for ( auto token = ret.begin(); token != ret.end(); ++token ){

            if(!(token->second.first == " " || token->second.first == "//")){

                if(token->second.second=="Variable"||token->second.second=="Identifier"){

                    cout.width(60);
                    if(count<10){
                        string double_digits = to_string(count);
                        double_digits = "0"+double_digits;
                        cout<<"\t Number of Token = " << double_digits << " "
                        << setw(10) << token->second.first << " "<< setw(25)<< token->second.second  <<setw(18);
                        fout<<"\t Token   No :"<<double_digits<< "  "<<setw(10)<< token->second.first << " " <<""<< setw(25)<< token->second.second  <<setw(18)<<endl;
                        Sleep(1500);
                    }
                    else{
                        cout<<"\t Number of Token = "<<count<< "   "<< setw(10)<< token->second.first << " " <<" "<< setw(25) << token->second.second  <<setw(18)<<" "<<endl;
                        fout<<"\t Number of Token = "<<count<< "   "<< setw(10)<< token->second.first << " " <<" "<< setw(25) << token->second.second  <<setw(18)<<" "<<endl;
                        Sleep(1500);
                    }
                    count++;
                }

                else{
                    if(token->second.second=="operationerator"){
                        cout.width(40);
                        string operation = convert[token->second.first];
                        if(count<10){
                            string double_digits = to_string(count);
                            double_digits = "0"+double_digits;
                            cout<<"\t Number of Token = "<<double_digits<< "  " << setw(10) << token->second.first << " " << setw(25)<< token->second.second<<" , "<<operation << "    "  <<endl;
                            fout<<"\t Number of Token = "<<double_digits<< " "<< setw(10)<< token->second.first << " " <<" "<< setw(25)<< token->second.second<<" , "<<operation<<"    "  <<endl;
                            count++;
                        }
                        else{
                            cout<<"\t Number of Token = "<<count<< "   "<< setw(10)<< token->second.first << " " <<" "<< setw(25)<< token->second.second<<" , "<<operation<<"    "  <<endl;
                            fout<<"\t Number of Token = "<<count<< "   "<< setw(10)<< token->second.first << " " <<" "<< setw(25)<< token->second.second<<" , "<<operation<<"    "  <<endl;
                            Sleep(1500);
                            count++;
                        }

                    }
                    else{
                        cout.width(40);
                        if(count<10){
                            string double_digits = to_string(count);
                            double_digits = "0"+double_digits;
                            cout<<"\t Number of Token = "<<double_digits<< "   "<< setw(10)<< token->second.first << " " <<" "<< setw(25)<< token->second.second<<"    "  <<endl;
                            fout<<"\t Number of Token = "<<double_digits<< "   "<< setw(10)<< token->second.first << " "<<" "<< setw(25)<< token->second.second<<"    "  <<endl;
                            count++;
                        }
                        else{
                            cout<<"\t Number of Token = "<<count<< "   "<<setw(10)<< token->second.first << " " <<" "<< setw(25)<< token->second.second<<"    "  <<endl;
                            fout<<"\t Number of Token = "<<count<< "    "<<setw(10)<< token->second.first << " " <<" "<< setw(25)<< token->second.second<<"    "  <<endl;
                            count++;
                        }

                    }

                }
            }
        }

    }

    else{
        cout.fill(' ');
        cout.width(40);
        cout<<"\n FILE NOT FOUND!\n\n";
    }
    return 0;
}