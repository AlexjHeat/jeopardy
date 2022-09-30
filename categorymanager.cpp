#include "categorymanager.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <algorithm>
//#include <QFileDialog>

///CONSTRUCTORS///
CategoryManager::CategoryManager() {
}


int CategoryManager::count() {
    return mCategories.count();
}

///PUBLIC METHODS///
bool CategoryManager::addCategory(Category* category) {
    //Check if new category title already exists
    QStringList titleList = getStringList();
    for (int index = 0; index < count(); index++) {
        if (category->getTitle().compare(titleList[index], Qt::CaseInsensitive) == 0) {
            return false;
        }
    }
    mCategories.append(category);
    sort();
    return true;
}

bool CategoryManager::removeCategory(int index) {
    if (index < count()) {
        mCategories.removeAt(index);
        return true;
    }
    return false;
}

bool CategoryManager::removeCategory(QString title) {
    QStringList titleList = getStringList();
    for (int index = 0; index < count(); index++) {
        if (title.compare(titleList[index], Qt::CaseInsensitive) == 0) {
            mCategories.removeAt(index);
            return true;
        }
    }
    return false;
}

Category* CategoryManager::getCategory(int index) {
    if (index < count()) {
        return mCategories[index];
    }
    return NULL;
}

Category* CategoryManager::getCategory(QString title) {
    QStringList titleList = getStringList();
    for (int index = 0; index < count(); index++) {
        if (title.compare(titleList[index], Qt::CaseInsensitive) == 0) {
            return mCategories[index];
        }
    }
    return NULL;
}
QString CategoryManager::getTitle(int index) {
    if (index < count()) {
        return mCategories[index]->getTitle();
    }
    return NULL;
}

void CategoryManager::setTitle(int index, QString title) {
    if (index < count()) {
        mCategories[index]->setTitle(title);
    }
}

QString CategoryManager::getTag(int index) {
    if (index < count()) {
        return mCategories[index]->getTag();
    }
    return NULL;
}

void CategoryManager::setTag(int index, QString tag) {
    if (index < count()) {
        mCategories[index]->setTag(tag);
    }
}


QString CategoryManager::getDescription(int index) {
    if (index < count()) {
        return mCategories[index]->getDescription();
    }
    return NULL;
}

void CategoryManager::setDescription(int index, QString description)   {
    if (index < count()) {
        mCategories[index]->setDescription(description);
    }
}

Question CategoryManager::getQuestion(int index, int q) {
    if (index < count()) {
        return mCategories[index]->getQuestion(q);
    }
    return Question();
}


void CategoryManager::setQuestion(int index, int q, Question question) {
    if (index < count()) {
        mCategories[index]->setQuestion(q, question);
    }
}

QList<Question> CategoryManager::getQuestions(int index) {
    QList<Question> questions;
    if (index < count()) {
        return mCategories[index]->getQuestions();
    }
    return questions;
}

void CategoryManager::setQuestions(int index, QList<Question> questions) {
    if (index < count()) {
        mCategories[index]->setQuestions(questions);
    }
}

bool CategoryManager::save(QString filename) {
    //TODO use QRegExpr to save files without sacrifcing use of '\' and '|'
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Failed to save categories: " + file.errorString());
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i < count(); i++) {
        out << mCategories[i]->toString() << "\n";
    }
    file.flush();
    file.close();
    return true;
}

bool CategoryManager::load(QString filename) {

    //QString fileName = QFileDialog::getOpenFileName(nullptr, "Load Category File", "", "(*.txt)");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Failed to load categories: " + file.errorString());
        return false;
    }
    QTextStream in(&file);
    //QMessageBox::warning(nullptr, "Error", in.readLine());
    //QMessageBox::warning(nullptr, "Error", in.readAll());
    while(!in.atEnd()) {
        Category* category = new Category();
        category->fromString(in.readLine());
        mCategories.append(category);
    }
    file.flush();
    file.close();
    return true;
}

QStringList CategoryManager::getStringList() {
    QStringList categoryList;
    for (Category* category : this->mCategories) {
        categoryList.append(category->getTag() + " - " + category->getTitle());
    }
    return categoryList;
}

///PRIVATE METHODS///
void CategoryManager::sort() {
    for (int i  = 0; i < count(); i++) {
        int iMin = i;
        for (int j = i + 1; j < count(); j++) {
            if (*mCategories[j] < *mCategories[iMin]) {
                //QMessageBox::warning(nullptr, "Error", mCategories[j]->getTitle() + "<" + mCategories[iMin]->getTitle());
                iMin = j;

            }
        }
        Category* temp = mCategories[i];
        mCategories[i] = mCategories[iMin];
        mCategories[iMin] = temp;
    }

    //std::sort(mCategories.begin(), mCategories.end());
    //TODO implement faster sorting
}
