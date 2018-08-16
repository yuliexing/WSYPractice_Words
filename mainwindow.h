#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "kanawordlist.h"
#include "practice.h"
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void init();
    bool dealWithStart();
    bool dealWithEnd();
    void getNextWord();
    void setSourceFile(QString fileName = "");
    void setIsAutoInput(bool value);
    
public slots:
    void dealWithSelectAllStateChange(int state);
    void dealWithSelectSectionChange();
    void dealWithStartButtonClicked();
    void dealWithSecondPast();
    void dealWithSubmitButtonClicked();
    void dealWithHelpButtonClicked();
    void dealWithListItemDoubleClick(QListWidgetItem *item);
    void dealWithShowAllWordBtnClicked();
private:
    Ui::MainWindow *ui;
    KanaWordList kanaWordList;
    Practice practice;
    
    bool isAutoInput = false;
    
    bool isSectionSelectChange;
    bool isStart;
    
    bool isWord;
    bool isExpl;
    bool isJpns;
    bool isKana;
    
    int totalCount, correctCount, errorCount;
    KanaWord curWord;
    
    int coustTime;
    QTimer coustTimer;
};

#endif // MAINWINDOW_H
