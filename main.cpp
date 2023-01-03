#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "hashtable.h"
#include "linkedList.h"

int main()
{
    const clock_t begin = clock();

    hashtable mainStorage(160000);

    linkedList dividedText;
    linkedList stopWordsList;

    size_t firstCharFound, lastCharFound, firstCharIndex, lastIntIndex;
    int countOfSupra;

    int index, newDigit, oldDigit, newCount;

    std::string tempWord, tempLine;

    //----------------------------------------------------------------------------------------------------------------------

    std::ifstream publicationsDataSetFile("PublicationsDataSet.txt");

    std::ifstream stopWordsFile("stopwords.txt");

    if (!publicationsDataSetFile.is_open())
    {
        std::cerr << "File can not be opened" << std::endl;
    }
    if (!stopWordsFile.is_open())
    {
        std::cerr << "File can not be opened" << std::endl;
    }

    //----------------------------------------------------------------------------------------------------------------------

    while (std::getline(publicationsDataSetFile, tempLine)) //  until find UnigramCount
    {

        int deletionPoint = (int)tempLine.find("\"unigramCount\":");
        tempLine = tempLine.substr((deletionPoint + 16), tempLine.length() - (deletionPoint + 18));
        dividedText.insert(tempLine);
    }

    while (std::getline(stopWordsFile, tempLine))
    {
        stopWordsList.insert(tempLine);
    }

    //----------------------------------------------------------------------------------------------------------------------

    for (int i = 0; i < dividedText.getCount(); i++)
    {
        lastCharFound = 0;
        index = 0;
        newDigit = 0;

        const std::string &text = dividedText.moveToNextAndGetData();

        while (lastCharFound + 6 < text.length())
        {

            newCount = 0;
            firstCharFound = text.find('\"', lastCharFound);

            if (firstCharFound + 1 != std::string::npos)
            {
                lastCharFound = text.find("\":", firstCharFound + 1);
            }

            while (isdigit(lastCharFound + 2))
            {
                lastCharFound = text.find("\":", lastCharFound + 1);
                std::cout << lastCharFound << std::endl;
            }

            //                lastIntIndex=text.find(',', lastCharFound+1);//***
            //                std::cout << countOfSupra << std::endl;
            //                std::cout << text.substr(lastCharFound + 2,lastIntIndex) << std::endl;
            //            countOfSupra = std::stoi(text.substr(lastCharFound ,lastIntIndex));
            //            std::cout << countOfSupra << std::endl;
            //            oldDigit = newDigit;
            //            newDigit = 1;

            //            while (text[lastCharFound + 2 + newDigit] <= '9' && text[lastCharFound + 2 + newDigit] >= '0')
            //            {
            //                newDigit++;
            //            }
            //            if ((lastCharFound + 2 + newDigit) < text.length())
            //            {
            //                if (text[lastCharFound + 2 + newDigit] != ',')
            //                {
            //                    lastCharFound = text.find("\":", lastCharFound + 1);
            //                }
            //            }
            //
            //            newDigit = 0;
            //
            //            while (text[lastCharFound + 2 + newDigit] <= '9' && text[lastCharFound + 2 + newDigit] >= '0')
            //            {
            //                newCount = newCount * 10;
            //                newCount += text[lastCharFound + 2 + newDigit] - '0';
            //                newDigit++;
            //            }

            if (index == 0)
            {
                firstCharIndex = firstCharFound + 1;
            }
            else
            {
                firstCharIndex = firstCharFound + 4 + oldDigit;
            }

            tempWord = text.substr(firstCharIndex, lastCharFound - firstCharIndex);

            if (checkWord(tempWord))
            {

                mainStorage.insert(tempWord, countOfSupra);
            }
            index++;
        }
    }

    //----------------------------------------------------------------------------------------------------------------------

    for (int i = 0; i < stopWordsList.getCount(); i++)
    {
        mainStorage.remove(stopWordsList.at(i));
    }

    const wordCount *top10 = mainStorage.top10();

    for (int i = 0; i < 10; i++)
    {
        std::cout << top10[i].count << " " << top10[i].word << std::endl;
    }

    const clock_t end = clock();
    std::cout << "Total Elapsed Time " << (end - begin) << " miliseconds" << std::endl;

    delete[] top10;
}