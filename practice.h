#ifndef PRACTICE_H
#define PRACTICE_H

#include <QString>
#include <QVector>

#include "kanaword.h"

class Practice
{
public:
    Practice();
    void init();

    QVector<KanaWord> getSourceList() const;
    void setSourceList(const QVector<KanaWord> &value);
    
    QVector<KanaWord> getPracticeList() const;
    void setPracticeList();
    
    KanaWord randomChoose();
    KanaWord getOneWord();
private:
    QVector<KanaWord> sourceList;
    QVector<KanaWord> practiceList;
    
    KanaWord curWord;
    KanaWord nextWord;
    
    int practiceListSize;
};

#endif // PRACTICE_H
