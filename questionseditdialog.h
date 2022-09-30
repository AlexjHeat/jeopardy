#ifndef QUESTIONSEDITDIALOG_H
#define QUESTIONSEDITDIALOG_H

#include <QDialog>
#include "categorymanager.h"

namespace Ui {
class QuestionsEditDialog;
}

class QuestionsEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionsEditDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager, int index);
    ~QuestionsEditDialog();

private:
    Ui::QuestionsEditDialog *ui;
    std::shared_ptr<CategoryManager> mCategoryManager;
    int mIndex;
};

#endif // QUESTIONSEDITDIALOG_H
