#include "category.h"
#include <QRegularExpression>
#include <QMessageBox>

static QString clean(QString s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '|' || s[i] == '\\') {
            s.remove(i, 1);
        }
    }
    return s;
}

///CONSTRUCTORS///ww
Category::Category() {
}

Category::Category(QString title, QString tag, QString description)
    : mTitle(clean(title)),
      mTag(clean(tag).toUpper()),
      mDescription(clean(description)) {
}

///PUBLIC METHODS///
QString Category::getTitle() { return mTitle; }
void Category::setTitle(QString title) { mTitle = clean(title); }

QString Category::getTag() { return mTag; }
void Category::setTag(QString tag) { mTag = tag.toUpper(); }

QString Category::getDescription() { return mDescription; }
void Category::setDescription(QString description) { mDescription = clean(description); }

Question Category::getQuestion(int i) { return mQuestions[i]; }
void Category::setQuestion(int i, Question question) { mQuestions[i] = question; }

QList<Question> Category::getQuestions() {
    QList<Question> questions;
    for (int i = 0; i < QUESTIONS_PER_CATEGORY; i++) {
        questions.append(mQuestions[i]);
    }
    return questions;
}
void Category::setQuestions(QList<Question> questions) {
    if (questions.count() < QUESTIONS_PER_CATEGORY) { return; }
    for (int i = 0; i < QUESTIONS_PER_CATEGORY; i++) {
        mQuestions[i] = questions[i];
    }
}

QString Category::toString() {
    QString result =
            mTitle + "\\" +
            mTag + "\\" +
            mDescription;
    for (int i = 0; i < QUESTIONS_PER_CATEGORY; i++) {
        result += "\\" + mQuestions[i].toString();
    }
            return result;
}

void Category::fromString(QString str) {
    QStringList fields = str.split(QChar('\\'));
    int i = 0;
    mTitle = fields[i++];
    mTag = fields[i++];
    mDescription = fields[i++];
    for (int j = 0; i < QUESTIONS_PER_CATEGORY; i++){
        mQuestions[j].fromString(fields[i++]);
    }
}

bool Category::operator<(Category category) {
    QString thisString = (mTag + mTitle).toUpper();
    QString comparisonString = (category.getTag() + category.getTitle()).toUpper();
    return (thisString < comparisonString);
}
