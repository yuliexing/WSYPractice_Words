#include "practice.h"

#include <QTime>

Practice::Practice()
{
    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
}

void Practice::init()
{
    this->sourceList.clear();
    this->practiceList.clear();
    this->practiceListSize = 0;
}

QVector<KanaWord> Practice::getSourceList() const
{
    return sourceList;
}

void Practice::setSourceList(const QVector<KanaWord> &value)
{
    sourceList = value;
    this->practiceListSize = this->sourceList.size() * 0.7;
    this->practiceList.clear();
}

QVector<KanaWord> Practice::getPracticeList() const
{
    return practiceList;
}

void Practice::setPracticeList()
{
    if (this->sourceList.size() == 0)
        return;
    
    do {
        KanaWord kw = randomChoose();
        if (this->practiceList.contains(kw))
        {
            continue;
        }
        this->practiceList.push_back(kw);
    } while(this->practiceList.size() < this->practiceListSize);
}

KanaWord Practice::randomChoose()
{
    int i = 0;
    i = qrand() % this->sourceList.size();
    return this->sourceList[i];
}

KanaWord Practice::getOneWord()
{
    setPracticeList();
    KanaWord kw = this->practiceList.front();
    this->practiceList.pop_front();
    return kw;
}
