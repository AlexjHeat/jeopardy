#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "addcategorydialog.h"
#include "removecategorydialog.h"
#include "editcategorydialog.h"
#include "questionseditdialog.h"
#include <QMessageBox>

#define CATEGORY_FILE   "category_list.txt"
#define CATEGORY_AMOUNT 5

/*
    QMessageBox::warning(nullptr, "TEST", "");
 */

///CONSTRUCTORS///
ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
    , gameActive(false) {

    ui->setupUi(this);
    mCategoryManager = std::make_shared<CategoryManager>();
    mCategoryManager->load(CATEGORY_FILE);
    //TODO find way to backup save files
        //System automatically loads and saves from a hidden file that contains the most recent content upon exit
        //Can manually save to and load from external file through QFileDialog and mCategoryManager

    //UI Array Initializations
    mCategoryMenus = ui->centralwidget->findChildren<QComboBox*>(QRegularExpression("uCategoryComboMenu_\\d+"));
    mCategoryDescriptions = ui->centralwidget->findChildren<QLabel*>(QRegularExpression("uCategoryDescription_\\d+"));
    mQuestionButtons = ui->centralwidget->findChildren<QPushButton*>(QRegularExpression("uQuestionButton\\d+_\\d+"));
    mQuestionEdit = ui->centralwidget->findChildren<QPushButton*>(QRegularExpression("uEditQuestionsButton_\\d+"));
    resetCategoryMenus();

    //Signal/Slot Connections
    connect(this->ui->uCategoryLoad, SIGNAL(triggered()), this, SLOT(categoryLoadAction()));
    connect(this->ui->uCategorySave, SIGNAL(triggered()), this, SLOT(categorySaveAction()));
    connect(this->ui->uCategoryAdd, SIGNAL(triggered()), this, SLOT(categoryAddAction()));
    connect(this->ui->uCategoryRemove, SIGNAL(triggered()), this, SLOT(categoryRemoveAction()));
    connect(this->ui->uCategoryEdit, SIGNAL(triggered()), this, SLOT(categoryEditAction()));

    for (int col = 0; col < CATEGORY_AMOUNT; col++) {
        connect(this->mCategoryMenus[col], SIGNAL(activated(int)), this, SLOT(categoryChanged(int)));
    }

    //Connect each edit button
    for (int col = 0; col < CATEGORY_AMOUNT; col++) {
        connect(this->mQuestionEdit[col], SIGNAL(released()), this, SLOT(questionAction()));
    }
    //Connect each question button
    for (int col = 0; col < CATEGORY_AMOUNT; col++) {
        for (int q = 0; q < QUESTIONS_PER_CATEGORY; q++) {

        }
    }
}

///DESTRUCTOR///
ControlWindow::~ControlWindow() {
    delete ui;
}

///SLOTS///
bool ControlWindow::categoryLoadAction() {
    //return mCategoryManager->load();
     //Can manually save to and load from external file through QFileDialog and mCategoryManager
    return false;
}

bool ControlWindow::categorySaveAction() {
    //return mCategoryManager->save();
    //Can manually save to and load from external file through QFileDialog and mCategoryManager
    return false;
}

void ControlWindow::categoryAddAction() {
    AddCategoryDialog addCategoryDialog(this, mCategoryManager);
    addCategoryDialog.exec();
    resetCategoryMenus();
}


void ControlWindow::categoryRemoveAction() {
    RemoveCategoryDialog removeCategoryDialog(this, mCategoryManager);
    removeCategoryDialog.exec();
    resetCategoryMenus();
}

void ControlWindow::categoryEditAction() {
    EditCategoryDialog editCategoryDialog(this, mCategoryManager);
    editCategoryDialog.exec();
    resetCategoryMenus();
}

void ControlWindow::onExit() {
    mCategoryManager->save(CATEGORY_FILE);
}

///PRIVATE METHODS///
void ControlWindow::resetCategoryMenus() {
    for(int col = 0; col < this->mCategoryMenus.count(); col++) {
        mCategoryMenus[col]->clear();
    }
    for(int index = 0; index < this->mCategoryManager->count(); index++) {
        for(int col = 0; col < this->mCategoryMenus.count(); col++) {
            mCategoryMenus[col]->addItem(mCategoryManager->getTag(index) + " - " + mCategoryManager->getTitle(index));

            //might not need to apply categoryDescription here, might be better to due it in categoryChanged slot
            if (index == 0) {
                mCategoryDescriptions[col]->setText(mCategoryManager->getDescription(index));
            }
        }
    }
}

int ControlWindow::getColumn(QObject* sender) {
    QString name = sender->objectName();
    return name.back().digitValue();
}

///PRIATE SLOTS///
void ControlWindow::categoryChanged(int index) {
    int col = getColumn(QObject::sender());
    mCategoryDescriptions[col]->setText(mCategoryManager->getDescription(index));
}

void ControlWindow::questionAction() {
    if (gameActive) {
        return;
    }
    else {
        QComboBox* sender = static_cast<QComboBox*>(QObject::sender());
        int index = sender->currentIndex();
        QList<Question>  questions = mCategoryManager->getQuestions(index);
        QuestionsEditDialog questionsEditDialog(this, mCategoryManager, index);

    }

        //QComboBox* sender = static_cast<QComboBox*>(QObject::sender())
        //int index = sender.currentIndex()

        //new QuestionEditDialog(CategoryManager*, Question*)
}
