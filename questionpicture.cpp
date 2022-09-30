#include "questionpicture.h"

QuestionPicture::QuestionPicture()
{

}

QuestionPicture::QuestionPicture(int value, QString prompt, QString answer, QString fileLocation)
    : Question(value, prompt, answer),
      mFileLocation(fileLocation)
{}

QString QuestionPicture::getFileLocation() {return mFileLocation;}
void QuestionPicture::setFileLocation(QString fileLocation) {mFileLocation = fileLocation;}

QString QuestionPicture::toString()
{

}
