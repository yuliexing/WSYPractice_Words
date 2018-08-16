#ifndef KANAWORDLIST_H
#define KANAWORDLIST_H

#include <QString>
#include <QVector>
#include <QMap>

#include "kanaword.h"

class KanaWordList
{
public:
    KanaWordList(QString fileName = ":/rec/words.csv");
    void readWordsFile();
    QVector<KanaWord> getSectionWordList(QVector<QString> sectionTitle);
    
    void init(QString fileName);
    QVector<QString> getSectionList() const;
    
private:
    QString wordFileName;
    QVector<QString> sectionList;
    QMap<QString, QVector<KanaWord>> wordMap;
};

#endif // KANAWORDLIST_H
