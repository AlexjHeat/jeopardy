#include "questionseditdialog.h"
#include "ui_questionseditdialog.h"

QuestionsEditDialog::QuestionsEditDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager, int index):
    QDialog(parent),
    ui(new Ui::QuestionsEditDialog),
    mCategoryManager(categoryManager),
    mIndex(index)

{
    ui->setupUi(this);
}

QuestionsEditDialog::~QuestionsEditDialog()
{
    delete ui;
}
