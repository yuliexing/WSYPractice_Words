#include "kanaword.h"

KanaWord::KanaWord()
{

}

KanaWord::KanaWord(QString word, QString kana, QString explanation, QString tone, QString section)
{
    this->word = word;
    this->kana = kana;
    this->explanation = explanation;
    this->tone = tone;
    this->section = section;
}

QString KanaWord::getWord() const
{
    return word;
}

void KanaWord::setWord(const QString &value)
{
    word = value;
}

QString KanaWord::getKana() const
{
    return kana;
}

void KanaWord::setKana(const QString &value)
{
    kana = value;
}

QString KanaWord::getExplanation() const
{
    return explanation;
}

void KanaWord::setExplanation(const QString &value)
{
    explanation = value;
}

QString KanaWord::getTone() const
{
    return tone;
}

void KanaWord::setTone(const QString &value)
{
    tone = value;
}

QString KanaWord::getWordType() const
{
    return wordType;
}

void KanaWord::setWordType(const QString &value)
{
    wordType = value;
}

QString KanaWord::getSection() const
{
    return section;
}

void KanaWord::setSection(const QString &value)
{
    section = value;
}

bool KanaWord::operator==(const KanaWord &kw) const
{
    if (kw.word == this->word && kw.kana == this->kana && kw.explanation == this->explanation 
            && kw.tone == this->tone && kw.section == this->section)
        return true;
    return false;
}
