#include<iostream>
#include"Error.cpp"
#include<vector>

Error er;

class DDL{
    private:
        std::string tableName;
        std::string command;
        int index;
        std::vector<std::pair<std::string,std::string>> _tableInfo;  // [ {rowName, rowType} , ..... so on]
    public:
        DDL(){}
        DDL(const std::string _uCommand, int _index): command(_uCommand), index(_index){
            tableName = "";
        }

        void extractInfo(){
            while(command[index] == ' ') index++;
            extractTableName();

            std::string rowType = "", rowName = "";

            while(command[index] != '}'){
                while (command[index] == ' ' || command[index] == ',') index++;
                while(command[index] != ' '){
                    rowType.push_back(command[index]);
                    index++;
                }
          
                while (command[index] == ' ') index++;
                while(command[index] != ',' && command[index] != '}'){
                    rowName.push_back(command[index]);
                    index++;
                }

                _tableInfo.push_back({rowName,rowType});
                rowName.clear(); rowType.clear();
            }
        }


        void extractTableName(){
            std::string _tableName = "";
            char ch;
            while(command[index] == ' ') index++;
            while(command[index] != '{'){
                ch = command[index];
                _tableName.push_back(ch);
                index++; 
            }
            index++;
            tableName = _tableName;
            std::cout<<tableName<<" "<<index<<std::endl;
        }

        void showtableInfo(){
            for(std::pair<std::string, std::string> pr : _tableInfo){
                std::cout<<pr.first<<" ";
            }
            std::cout<<std::endl;
        }

        void CreateTable(){

        }
};

void Analyzer(const std::string& command, bool& isDDL, bool& isDML, bool& isDEL, int& _index){
    int index = 0, tempIndex = 0;
    std::string temp = "";
    while(command[index] != ':' && command[index] != '\n'){
        if(command[index] == ' '){
            index++;
            continue;
        }
        temp[tempIndex] = command[index];
        index++;
        tempIndex++;
    }

    _index = ++index;

    if(command[index] == '\n'){
        er.NoColonError();
        return;
    }

    if(temp.compare("Create")){
        isDDL = true;
        return;
    }
    if(temp.compare("Add")){
        isDML = true;
        return;
    }
    if(temp.compare("Show")){
        isDEL = true;
        return;
    }

}

int main(){
    std::string command = "Create:Student{int rollNo, string Name, int Marks}";
    bool isDDL = false, isDML = false, isDEL = false;
    int index;
    Analyzer(command, isDDL, isDML,isDEL , index);
     std::cout<<index<<" ";
    if(isDDL){
        DDL ddl(command, index);
        ddl.extractInfo();
        ddl.showtableInfo();
    }


    return 0;
}