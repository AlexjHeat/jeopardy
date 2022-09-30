#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question {
    public:
        Question();
        Question(int value, QString prompt, QString answer, QString fileLocation);

        int getValue();
        void setValue(int value);
        QString getPrompt();
        void setPrompt(QString prompt);
        QString getAnswer();
        void setAnswer(QString answer);
        QString getFileLocation();
        void setFileLocation(QString fileLocation);

        QString toString();
        void fromString(QString str);

    private:
        int mValue;
        QString mPrompt;
        QString mAnswer;
        QString mFileLocation;
};        

#endif // QUESTION_H
