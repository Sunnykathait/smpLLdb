#include <iostream>
#include <vector>
#include <string>


typedef struct TableNode
{
private:
    std::string data;
    std::string dataType;

public:
    struct TableNode* next;
    struct TableNode* down;

    TableNode()
    {
        next = NULL;
        down = NULL;
    }

    TableNode(std::string _dataType, std::string _data)
    {
        this->data = _data;
        this->dataType = _dataType;
        next = nullptr;
        down = nullptr;
    }

    void setDataType(std::string _dataType)
    {
        dataType = _dataType;
    }

    void setNextPtr(struct TableNode *temp)
    {
        next = temp;
    }

    void setData(std::string _data)
    {
        data = _data;
    }

    inline void showDataType()
    {
        std::cout << dataType << " -> ";
    }

    inline void showData()
    {
        std::cout << data <<" ";
    }
} Node;

class Table
{
private:
    std::string tableName;
    Node *pointer;
    int rowNo;
    int length;

public:
    Table()
    {
        tableName = nullptr;
        pointer = nullptr;
        rowNo = 0;
        length = 0;
    }

    Table(std::string _tableName) : tableName(_tableName)
    {
        pointer = nullptr;
        rowNo = 0;
        length = 0;
    }

    void initalizeTableDT(std::vector<std::pair<std::string, std::string>> _typeList)
    {
        Node* Head = NULL;
        Node* temp = NULL;
        for (std::pair<std::string, std::string> _dataTypeElement : _typeList)
        {
            if (Head == NULL)
            {
                length++;
                Head = new Node();

                Head->setDataType(_dataTypeElement.first);
                Head->next = new Node();
                temp = Head->next;
            }
            else
            {
                length++;
                temp->setDataType(_dataTypeElement.first);
                temp->next = new Node();
                temp = temp->next;
            }
        }
        pointer = Head;
    }

    Node* getPointer()
    {
        return this->pointer;
    }

    std::string getTableName()
    {
        return this->tableName;
    }

    void addRow(std::vector<std::string> dataItems)
    {
        Node* temp = pointer;
        Node* tempDown = nullptr;
        int index = 0;

        if (getRowNo() == 0)
        {
            if(!pointer)
            {
                std::cout<<"Table is empty\n";
                return;
            }
            
            while (temp->next)
            {
                temp->down = new Node("", dataItems[index++]);
                temp = temp->next;
            }
        }
        else
        {
            while(temp->next)
            {
                tempDown = temp;
                while (tempDown->down)
                {
                    tempDown = tempDown->down;
                }
                tempDown->down = new Node("", dataItems[index++]);
                temp = temp->next;
            }
        }

        rowNo++;

        std::cout << "Row added successfully\n";
    }

    int getRowNo()
    {
        return rowNo;
    }

    void showTable()
    {
        Node* temp = pointer;
        Node* tempDown = nullptr;

        if (!pointer) {
            std::cout << "Table is empty\n";
            return;
        }

        while (temp)
        {
            tempDown = temp->down;
            temp->showDataType();
            while(tempDown)
            {
                tempDown->showData();
                tempDown = tempDown->down;
            }
            std::cout << std::endl;
            temp = temp->next;
        }
    }
};