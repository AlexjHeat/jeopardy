#ifndef QUESTIONPICTURE_H
#define QUESTIONPICTURE_H

#include "question.h"

class QuestionPicture : public Question
{
    public:
        QuestionPicture();
        QuestionPicture(int, QString, QString, QString);
        QString getFileLocation();
        void setFileLocation(QString);
        QString toString();

    protected:
        QString mFileLocation;
};

#endif // QUESTIONPICTURE_H
