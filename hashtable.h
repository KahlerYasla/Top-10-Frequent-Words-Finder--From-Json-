#ifndef CMP2003DENEME1_HASHTABLE_H
#define CMP2003DENEME1_HASHTABLE_H

struct wordCount
{
    std::string word;
    int count;
};

bool checkWord(std::string &word)
{

    // ,abc, ,abc! aBc. = abc;
    // ilk ve son harf arası harf mi diye kontrol et
    // ilk ve son indexe bak harf ise true
    // değil ise noktalama işaretini sil ve kelimeyi al

    bool flag1 = false;

    if (word.length() > 1)
    {
        if (!std::isalpha(word[0]))
        {
            // word.erase(0,1);
            flag1 = true;
        }
        if (!std::isalpha(word[word.length() - 1]))
        {
            // word.erase(word.length()-1,word.length());
            flag1 = true;
        }
        // std::cout<<word<<std::endl;
        //  ab-c
        if (flag1)
        {
            for (int i = 0; !std::isalpha(word[i]); i++)
            {
                if (word.length() < 2)
                {
                    return false;
                }

                else
                {
                    if (word.length() == 2)
                    {
                        break;
                    }
                    word.erase(0, 1);
                    //                    std::cout<<word<<std::endl;
                    //                    std::cout<<word.length()<<std::endl;
                }
            }

            //            std::cout<<word<<std::endl;
            for (int i = word.length() - 1; !std::isalpha(word[i]); i--)
            {
                if (word.length() < 2)
                {
                    return false;
                }
                else if (word.length() == 2)
                {
                    break;
                }
                else
                {
                    word.erase(i, i + 1);
                }
            }
        }

        // std::cout<<word<<std::endl;
        for (int i = 0; i < (int)word.length(); i++)
        {
            if (!((word[i] >= 'a' && word[i] <= 'z') ||
                  (word[i] >= 'A' && word[i] <= 'Z') ||
                  word[i] == '\'') ||
                word.length() < 2)
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

class hashtable
{
public:
    wordCount *table;
    int length;
    int size;

    //---------------------------------------------------------------------------------------------
    hashtable(int size_)
    {
        size = size_;
        table = new wordCount[size];
        length = 0;

        for (int i = 0; i < size; i++)
        {
            table[i].word = "";
            table[i].count = -1;
        }
    }
    ~hashtable()
    {
        delete[] table;
    }

    //----------------------------------------------------------------------------------------------

    void insert(std::string &word, const int count_)
    {
        int hashIndex = 0;
        int probingIteration = 0;

        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] >= 'A' && word[i] <= 'Z')
            {

                word[i] = word[i] + ('a' - 'A');
            }
        }

        for (unsigned int i = 0; i < word.length(); i++)
        {
            hashIndex += word[i]; // ascii values sum
        }

        while (probingIteration < size)
        {
            if (table[(hashIndex + (probingIteration * probingIteration)) % size].word == word)
            {
                table[(hashIndex + (probingIteration * probingIteration)) % size].count += count_;
                length++;

                return;
            }
            else
            {
                if (table[(hashIndex + (probingIteration * probingIteration)) % size].count == -1)
                {
                    table[(hashIndex + (probingIteration * probingIteration)) % size].word = word;
                    table[(hashIndex + (probingIteration * probingIteration)) % size].count = count_;
                    length++;
                    return;
                }
                else
                {
                    probingIteration++;
                }
            }
        }
    }

    void remove(const std::string &deleteWord) const
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i].word == deleteWord)
            {
                table[i].word = "";
                table[i].count = -1;
                return;
            }
        }
    }

    wordCount *top10() const
    {

        wordCount *sortedList = new wordCount[10];
        wordCount *tempList = new wordCount[size];

        for (int i = 0; i < size; i++)
        {
            tempList[i].count = table[i].count;
            tempList[i].word = table[i].word;
        }

        int max;
        int maxPosition;

        for (int i = 0; i < 10; i++)
        {
            sortedList[i].count = -1;
            sortedList[i].word = "";
        }

        for (int i = 0; i < 10; i++)
        {

            max = 0;
            maxPosition = 0;

            for (int j = 0; j < size; j++)
            {
                if (tempList[j].count > max)
                {
                    max = tempList[j].count;
                    maxPosition = j;
                }
            }
            sortedList[i] = tempList[maxPosition];
            tempList[maxPosition].count = -1;
            tempList[maxPosition].word = "";
        }
        delete[] tempList;
        return sortedList;
    }
};

#endif // CMP2003DENEME1_HASHTABLE_H
