#include "kanawordlist.h"
#include <QFile>
#include <QRegExp>

KanaWordList::KanaWordList(QString fileName)
{
    init(fileName);
}

void KanaWordList::init(QString fileName)
{
    this->wordFileName = fileName;
    readWordsFile();
}

QVector<QString> KanaWordList::getSectionList() const
{
    return sectionList;
}

void KanaWordList::readWordsFile()
{
    this->wordMap.clear();
    this->sectionList.clear();
    
    QFile file(this->wordFileName);
    if ( !file.exists() )
    {
        return;
    }

    QString pat=QString::fromLocal8Bit("(.*),(.*),(.*),(.*)");
    QRegExp reg(pat);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString sectionTitle = "Other";
    while (true)
    {
        QString line = QString( file.readLine() ).replace( "\n", "" );
        int pos = reg.indexIn(line);
        if (pos > -1)
        {
            QString word = reg.cap(1);
            QString kana = reg.cap(2);
            QString explanation = reg.cap(3);
            QString tone = reg.cap(4);
            if (kana != "")
            {
                QMap<QString, QVector<KanaWord>>::iterator iterator = this->wordMap.find(sectionTitle);
                QVector<KanaWord> kanaWordList;
                if (iterator != this->wordMap.end())
                {
                    kanaWordList = iterator.value();
                }
                kanaWordList.append(KanaWord(word, kana, explanation, tone, sectionTitle));
                this->wordMap.insert(sectionTitle, kanaWordList);
            }

            if (word != "" && kana == "")
            {
                sectionTitle = word;
                this->sectionList.append(sectionTitle);
            }
        }
        if (file.atEnd())
        {
            break;
        }
    }
    file.close();
}

QVector<KanaWord> KanaWordList::getSectionWordList(QVector<QString> sectionTitle)
{
    QVector<KanaWord> retList;
    if (sectionTitle.size() != 0)
    {
        for (QString title : sectionTitle)
        {
            auto iterator = this->wordMap.find(title);
            if (iterator != this->wordMap.end())
            {
                retList.append(iterator.value());
            }
        }
    }
    else
    {
        for(auto i : this->wordMap.values())
        {
            retList.append(i);
        }
    }
    return retList;
}
