#ifndef CMP2003DENEME1_LINKEDLIST_H
#define CMP2003DENEME1_LINKEDLIST_H

class linkedList
{
private:
    struct node
    {
        std::string data;
        node *link;
    };

    node *first;
    node *last;
    node *current;

    int count;

public:
    linkedList()
    {
        first = nullptr;
        last = nullptr;
        current = nullptr;
        count = 0;
    }

    ~linkedList()
    {
        deleteAllNodes();
    }

    void deleteAllNodes()
    {
        node *nodeIterator = first;
        while (nullptr != nodeIterator)
        {
            node *nodeToDelete = nodeIterator;
            nodeIterator = nodeIterator->link;
            delete nodeToDelete;
        }
    }

    int getCount() const
    {
        return count;
    }

    void insert(std::string newData)
    {
        node *newNode = new node;
        newNode->data = newData;
        newNode->link = nullptr;

        if (last != nullptr)
        {
            last->link = newNode;
            last = newNode;
        }
        else
        {
            first = newNode;
            last = newNode;
            current = newNode;
            newNode->link = nullptr;
        }
        count++;
    }

    std::string at(int position) const
    {
        node *temp = first;
        for (int i = 0; i < position; i++)
        {
            temp = temp->link;
        }
        return temp->data;
    }

    const std::string &moveToNextAndGetData()
    {
        while (current->link != nullptr)
        {
            std::string &data = current->data;
            current = current->link;
            return data;
        }
    }
};

#endif // CMP2003DENEME1_LINKEDLIST_H
