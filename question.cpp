#include "question.h"
#include <QRegularExpression>

static QString clean(QString s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '|' || s[i] == '\\') {
            s.remove(i, 1);
        }
    }
    return s;
}

///CONSTRUCTORS///
Question::Question() {
}

Question::Question(int value, QString prompt, QString answer, QString fileLocation = "")
    : mValue(value),
      mPrompt(clean(prompt)),
      mAnswer(clean(answer)),
      mFileLocation(clean(fileLocation)) {
}

///PUBLIC METHODS///
int Question::getValue() { return mValue; }
void Question::setValue(int value) { mValue = value; }

QString Question::getPrompt() { return mPrompt; }
void Question::setPrompt(QString prompt) { mPrompt = clean(prompt); }

QString Question::getAnswer() { return mAnswer; }
void Question::setAnswer(QString answer) { mAnswer = clean(answer); }

QString Question::getFileLocation() { return mFileLocation; }
void Question::setFileLocation(QString fileLocation) { mFileLocation = clean(fileLocation); }


QString Question::toString() {
    QString result =
            QString::number(mValue) +
            "|" + mPrompt +
            "|" + mAnswer +
            "|" + mFileLocation;
    return result;
}

void Question::fromString(QString str) {
    QStringList fields = str.split(QChar('|'));
    mValue = fields[0].toInt();
    mPrompt = fields[1];
    mAnswer = fields[2];
    mFileLocation = fields[3];
}
