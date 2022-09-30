#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include "category.h"
#include <QVector>

class CategoryManager {
public:
    CategoryManager();
    int count();

    bool addCategory(Category* category);
    bool removeCategory(int i);
    bool removeCategory(QString title);
    Category* getCategory(int i);
    Category* getCategory(QString title);

    QString getTitle(int index);
    void setTitle(int index, QString title);
    QString getTag(int index);
    void setTag(int index, QString tag);
    QString getDescription(int index);
    void setDescription(int index, QString description);
    Question getQuestion(int index, int q);
    void setQuestion(int index, int q, Question question);
    QList<Question> getQuestions(int index);
    void setQuestions(int index, QList<Question> questions);

    bool save(QString filename);
    bool load(QString filename);

    QStringList getStringList();

private:
    void sort();

    QList<Category*> mCategories;
};

#endif // CATEGORYMANAGER_H
