#include <iostream>
#include <vector>
#include <string>

typedef struct TableNode
{
private:
    std::vector<struct TableNode*>pathToAll;
    std::string data;
    std::string dataType;

public:
    struct TableNode *next;
    struct TableNode *down;

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

    void addTableNodeTOParent(struct TableNode* node){
        pathToAll.push_back(node);
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
        int remSize;
        remSize = 16 - dataType.size();
        std::string str1(remSize/2-1,' ');
        std::string str2(remSize/2, ' ');
        str1 = str1+ dataType + str2;
        std::cout<<str1;
    }

    inline void showData()
    {
        int remSize;
        remSize = 16 - data.size();
        std::string str1(remSize/2-1,' ');
        std::string str2(remSize/2, ' ');
        str1 = str1+ data + str2;
        std::cout<<str1;
    }
} Node;

class Table
{
private:
    std::string tableName;
    Node* pointer;
    Node* parentNode;
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
        Node *Head = NULL;
        Node *temp = NULL;
        for (std::pair<std::string, std::string> _dataTypeElement : _typeList)
        {
            if (Head == NULL)
            {
                length++;
                Head = new Node();
                parentNode = Head;

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

    Node *getPointer()
    {
        return this->pointer;
    }

    std::string getTableName()
    {
        return this->tableName;
    }


    void addRow(std::vector<std::string> dataItems)
    {
        if (dataItems.empty())
        {
            std::cerr << "Error: Cannot add an empty row.\n";
            return;
        }

        Node *temp = nullptr;
        Node *tempDown = nullptr;
        Node *prevDown = nullptr;

        bool isFirst = true;
        int index = 0;

        if (getRowNo() == 0)
        {
            if (!pointer)
            {
                std::cerr << "Error: Pointer is uninitialized.\n";
                return;
            }

            temp = pointer;
            while (temp && index < dataItems.size()) // Bounds check
            {
                
                temp->down = new Node("", dataItems[index]);
                if(isFirst){    
                    pointer->addTableNodeTOParent(temp->down);
                    isFirst = false;
                }
                if (prevDown == nullptr)
                {
                    prevDown = temp->down;
                }
                else
                {
                    prevDown->next = temp->down;
                    prevDown = prevDown->next;
                }
                index++;
                temp = temp->next;
            }
        }
        else
        {
            temp = pointer;
            while (temp && temp->next)
            {

                tempDown = temp;
                while (tempDown->down)
                {
                    tempDown = tempDown->down;
                }

                if (index >= dataItems.size())
                {
                    std::cerr << "Error: Insufficient data items.\n";
                    return;
                }

                tempDown->down = new Node("", dataItems[index++]);

                if(isFirst){    
                    pointer->addTableNodeTOParent(temp->down);
                    isFirst = false;
                }

                temp = temp->next;

                if (prevDown == nullptr)
                {
                    prevDown = tempDown->down;
                }
                else
                {
                    prevDown->next = tempDown->down; 
                    prevDown = prevDown->next;
                }
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
        Node *temp = pointer;
        Node *tempDown = nullptr;
        Node *tempPrevDown = nullptr;

        if (!pointer)
        {
            std::cout << "Table is empty\n";
            return;
        }

        tempDown = temp->down;

        while (temp)
        {
            temp->showDataType();
            temp = temp->next;
        }
        std::cout << "\n";
        while (tempDown)
        {
            tempPrevDown = tempDown;
            while (tempPrevDown)
            {
                tempPrevDown->showData();
                tempPrevDown = tempPrevDown->next;
            }
            tempDown = tempDown->down;
            std::cout << "\n";
        }
    }
};
