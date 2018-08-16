#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowIcon(QIcon(":/rec/ico.ico"));
    this->setFixedHeight(250);
    connect(ui->selectAllCheckBox, &QCheckBox::stateChanged, this, &MainWindow::dealWithSelectAllStateChange);
    connect(ui->sectionListWidget, &QListWidget::itemSelectionChanged, this, &MainWindow::dealWithSelectSectionChange);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::dealWithStartButtonClicked);
    connect(&this->coustTimer, &QTimer::timeout, this, &MainWindow::dealWithSecondPast);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::dealWithSubmitButtonClicked);
    connect(ui->helpButton, &QPushButton::clicked, this, &MainWindow::dealWithHelpButtonClicked);
    connect(ui->sectionListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::dealWithListItemDoubleClick);
    connect(ui->showAllWordBtn, &QPushButton::clicked, this, &MainWindow::dealWithShowAllWordBtnClicked);
    
    init();
}

void MainWindow::init()
{
    this->isStart = false;
    this->isSectionSelectChange = false;
    
    ui->sectionListWidget->clear();
    QVector<QString> sectionList = this->kanaWordList.getSectionList();
    ui->sectionListWidget->addItems(QList<QString>::fromVector(sectionList));
    ui->selectAllCheckBox->setChecked(false);
    
    ui->showBox->setVisible(this->isStart);
    ui->countBox->setVisible(this->isStart);
    
    ui->explRadioBtn->setChecked(true);
    ui->wordRadioBtn->setChecked(false);
    ui->jpnCheckBox->setChecked(true);
    ui->kanaCheckBox->setChecked(true);
    
    ui->wordLabel->setText("");
    ui->explLabel->setText("");
    ui->sectionLabel->setText("");
    ui->infoLabel->setText("");
    ui->helpButton->setEnabled(false);
    ui->submitButton->setEnabled(false);
    ui->showAllWordBtn->setEnabled(false);
    ui->startButton->setText("开");
    ui->kanaInputEdit->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSourceFile(QString fileName)
{
    if (fileName == "")
    {
        QString path = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV(*.csv)");
        if (path.length() == 0)
		{
			return;
		}
        fileName = path;
    }
    this->kanaWordList.init(fileName);
    init();
    if (ui->sectionListWidget->count() == 0)
    {
        ui->infoLabel->setText("空!");
    }
}

void MainWindow::dealWithSelectAllStateChange(int state)
{
    if (!isSectionSelectChange)
    {
        isSectionSelectChange = true;
        if (state == Qt::Checked)
        {
            ui->sectionListWidget->selectAll();
        }
        else if (state == Qt::PartiallyChecked)
        {
            ui->selectAllCheckBox->setCheckState(Qt::Checked);
            ui->sectionListWidget->selectAll();
        }
        else
        {
            ui->sectionListWidget->clearSelection();
        }
        ui->sectionListWidget->setFocus();
        isSectionSelectChange = false;
    }
}

void MainWindow::dealWithSelectSectionChange()
{
    if (!isSectionSelectChange)
    {
        isSectionSelectChange = true;
        int selectCount = ui->sectionListWidget->selectedItems().size();
        if (selectCount == 0)
        {
            ui->selectAllCheckBox->setCheckState(Qt::Unchecked);
        }
        else if (selectCount == ui->sectionListWidget->count())
        {
            ui->selectAllCheckBox->setCheckState(Qt::Checked);
        }
        else
        {
            ui->selectAllCheckBox->setCheckState(Qt::PartiallyChecked);
        }
        isSectionSelectChange = false;
    }
}

void MainWindow::dealWithStartButtonClicked()
{
    if (this->isStart ? dealWithEnd() : dealWithStart())
    {
        this->isStart = !this->isStart;
        ui->sectionGroupBox->setVisible(!this->isStart);
        ui->optionBox->setVisible(!this->isStart);
        ui->showBox->setVisible(this->isStart);
        ui->countBox->setVisible(this->isStart);
        
        ui->helpButton->setEnabled(this->isStart);
        ui->submitButton->setEnabled(this->isStart);
        ui->showAllWordBtn->setEnabled(this->isStart);
        ui->startButton->setText(this->isStart ?  "关" : "开");
        ui->kanaInputEdit->clear();
    }
}

bool MainWindow::dealWithStart()
{
    if (ui->sectionListWidget->count() == 0)
    {
        setSourceFile();
        return false;
    }
    auto itemList = ui->sectionListWidget->selectedItems();
    if (itemList.size() == 0)
    {
        ui->infoLabel->setText("选课!");
        return false;
    }
    QVector<QString> titleList;
    for (auto item : itemList)
    {
        titleList.append(item->text());
    }
    auto wordList = this->kanaWordList.getSectionWordList(titleList);
    if (wordList.size() == 0)
    {
        ui->infoLabel->setText("没词!");
        return false;
    }
    this->practice.setSourceList(wordList);
    
    this->totalCount = this->correctCount = this->errorCount = 0;
    ui->totalLabel->setText("0");
    ui->correctLabel->setText("0");
    ui->errorLabel->setText("0");
    ui->timeLabel->setText("00:00");
    ui->infoLabel->setText("");
    
    this->isWord = ui->wordRadioBtn->isChecked();
    this->isExpl = ui->explRadioBtn->isChecked();
    this->isJpns = ui->jpnCheckBox->isChecked();
    this->isKana = ui->kanaCheckBox->isChecked();
    
    if ( !(this->isJpns || this->isKana) )
    {
        this->isJpns = this->isKana = true;
        ui->jpnCheckBox->setChecked(true);
        ui->kanaCheckBox->setChecked(true);
    }
    
    this->setFixedHeight(130);
    getNextWord();
    return true;
}

bool MainWindow::dealWithEnd()
{
    ui->infoLabel->setText("");
    this->setFixedHeight(250);
    return true;
}

void MainWindow::getNextWord()
{
    auto kw = this->practice.getOneWord();
    if (this->isWord)
    {
        if (kw.getWord() != kw.getKana())
            ui->wordLabel->setText(kw.getWord());
        else
            ui->wordLabel->setText("");
        ui->explLabel->setText(kw.getExplanation());
    }
    if (this->isExpl)
    {
        ui->wordLabel->setText(kw.getExplanation());
        ui->explLabel->setText("");
    }
    
    QString otherInfo = "自: " + kw.getSection();
    ui->sectionLabel->setText(otherInfo);
    this->curWord = kw;
    
    this->coustTime = 0;
    this->coustTimer.stop();
    this->coustTimer.start(1000);
    ui->timeLabel->setText("00:00");
}

void MainWindow::dealWithSecondPast()
{
    this->coustTime++;
    ui->timeLabel->setText(QString::asprintf("%02d:%02d", this->coustTime / 60, this->coustTime % 60));
}

void MainWindow::dealWithSubmitButtonClicked()
{
    this->totalCount++;
    QString kanaInput = this->isAutoInput ? this->curWord.getKana() : ui->kanaInputEdit->text();
    ui->kanaInputEdit->clear();
    if ( (kanaInput == this->curWord.getKana() && this->isKana) || (kanaInput == this->curWord.getWord() && this->isJpns))
    {
        this->correctCount++;
        ui->infoLabel->setText("对");
        getNextWord();
    }
    else
    {
        this->errorCount++;
        ui->infoLabel->setText("错!");
        return;
    }
    ui->totalLabel->setText(QString::number(this->totalCount));
    ui->correctLabel->setText(QString::number(this->correctCount));
    ui->errorLabel->setText(QString::number(this->errorCount));
}

void MainWindow::dealWithHelpButtonClicked()
{
    ui->kanaInputEdit->setText(this->curWord.getKana());
}

void MainWindow::setIsAutoInput(bool value)
{
    isAutoInput = value;
}

void MainWindow::dealWithListItemDoubleClick(QListWidgetItem *item)
{
    ui->sectionListWidget->clearSelection();
    item->setSelected(true);
}

void MainWindow::dealWithShowAllWordBtnClicked()
{
    QString output;
    QVector<KanaWord> sourceList = practice.getSourceList();
    for (KanaWord word : sourceList)
    {
        output += word.getKana() + "\t" + word.getWord() + "\t" + word.getExplanation() + "\n";
    }
    QMessageBox::information(this, "", output);
}
