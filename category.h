#ifndef CATEGORY_H
#define CATEGORY_H

#include "board.h"
#include "question.h"
#include <QString>

#define QUESTIONS_PER_CATEGORY  5

class Category {
    public:
        Category();
        Category(QString title, QString tag, QString description);

        QString getTitle();
        void setTitle(QString title);
        QString getTag();
        void setTag(QString tag);
        QString getDescription();
        void setDescription(QString description);
        Question getQuestion(int i);
        void setQuestion(int i, Question question);
        QList<Question> getQuestions();
        void setQuestions(QList<Question> questions);

        QString toString();
        void fromString(QString str);

        bool operator<(Category category);

    private:
        QString mTitle;
        QString mTag;
        QString mDescription;
        Question mQuestions[QUESTIONS_PER_CATEGORY];
};

#endif // CATEGORY_H
