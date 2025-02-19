#include<map>
#include<string>
#include"Error.cpp"
#include"Table.cpp"
#include<iostream>

class TableStorage{
    private:
       std::vector<Table> alltable;

    public:
        void addTable(Table _table){
            alltable.push_back(_table);
            std::cout<<"Table "<<_table.getTableName()<<" created successfully\n";
        }

        void showtableDT(std::string _tableName){
            for(Table table : alltable){
                if(table.getTableName() == _tableName){
                    table.showTable();
                }
            }
        }

        void _addRow(std::string _tableName, std::vector<std::string> dataItems){
            for(Table& table : alltable){
                if(table.getTableName() == _tableName){
                    table.addRow(dataItems);
                }
            }            
        }

};