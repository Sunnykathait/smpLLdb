#include<vector>
#include"TableStorage.cpp"
#include<map>

Error er; // class to define all the errors
TableStorage allTable;
std::string _tableNameForDEL;

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

        int getNumberOfColums(){
            return _tableInfo.size();
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
        }

        void showtableInfo(){
            for(std::pair<std::string, std::string> pr : _tableInfo){
                std::cout<<pr.first<<" ";
            }
            std::cout<<std::endl;
        }

        void CreateTable(){
            extractInfo();
            Table table(tableName);
            _tableNameForDEL = tableName;
            table.initalizeTableDT(_tableInfo);
            allTable.addTable(table);
            
        }
};

// to work on this from , insert:<tableName>{item1/null,item2/null,item3,null,..... so on}
class DML{
    std::string tableName;
    std::string command;
    int index;
    std::vector<std::string> dataItems;

    public:
        DML(){

        }
        DML(const std::string _uCommand, int _index): command(_uCommand), index(_index){
            tableName = "";
        }

        void extractTableName(){
            std::string _tableName = "";
            char ch;
            while(command[index] == ' ') index++;
            while(command[index] != '('){
                ch = command[index];
                _tableName.push_back(ch);
                index++; 
            }
            index++;
            tableName = _tableName;
            // std::cout<<index<<" | "<<tableName<<"\n";
        }

        void extractDataItems(){
            extractTableName();
       
            std::string temp = "";
            while(command[index] != ')'){
                while(command[index] == ' ') {index++;}
                while(command[index] != ',' && command[index] != ')'){
                    temp.push_back(command[index]);
                    index++;
                }
                dataItems.push_back(temp);
                if(command[index] == ',') index++;
                temp = "";
            }
        }

        void showDataItem(){
            extractDataItems();
            for(std::string str : dataItems){
                std::cout<<str<<" ";
            }
            std::cout<<std::endl;
        }

        void executeDML(){
            extractDataItems();
            
            allTable._addRow(tableName, dataItems);
        }

};

void Analyzer(const std::string& command, bool& isDDL, bool& isDML, bool& isDEL, int& _index){
    int index = 0, tempIndex = 0;
    std::string temp;
    while(command[index] != ':' && command[index] != '\n'){
        if(command[index] == ' '){
            index++;
            continue;
        }
        temp.push_back( command[index]);
        index++;
        tempIndex++;
    }

    _index = ++index;

    if(command[index] == '\n'){
        er.NoColonError();
        return;
    }

    if(temp == "Create"){
        isDDL = true;
        return;
    }
    else if(temp == "Add"){
        isDML = true;
        return;
    }
    else if(temp == "Show"){
        isDEL = true;
        return;
    }
}


int main(){
    std::string command = "";
    
    bool isDDL, isDML, isDEL;
    int index;

    while(true){
        isDDL = false, isDML = false, isDEL = false;
        std::cout<<"Enter the command (wrtie exit to obvsly EXIT): \n";
        std::getline(std::cin, command);

        if(command == "exit") break;
        
        Analyzer(command, isDDL, isDML, isDEL, index);

        if(isDDL){
           
            DDL ddl(command, index);
            ddl.CreateTable();
        }
        else if(isDML){
            DML dml(command, index);
            
            dml.executeDML();
        }else if(isDEL){
            allTable.showtableDT(_tableNameForDEL);
        }
    }

    return 0;
}
