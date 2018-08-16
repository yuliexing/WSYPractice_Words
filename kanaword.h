#ifndef KANAWORD_H
#define KANAWORD_H

#include <QString>
#include <iostream>

class KanaWord
{
public:
    KanaWord();
    KanaWord(QString word, QString kana, QString explanation, QString tone, QString section);

    QString getWord() const;
    void setWord(const QString &value);

    QString getKana() const;
    void setKana(const QString &value);

    QString getExplanation() const;
    void setExplanation(const QString &value);

    QString getTone() const;
    void setTone(const QString &value);

    QString getWordType() const;
    void setWordType(const QString &value);

    QString getSection() const;
    void setSection(const QString &value);
    
    bool operator==(const KanaWord &kw) const;

private:
    QString word;           // 日文
    QString kana;           // 假名
    QString explanation;    // 释意
    QString tone;           // 音调
    QString wordType;       // 词性
    QString section;        // 所属单元
};

#endif // KANAWORD_H
