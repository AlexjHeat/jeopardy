#include "addcategorydialog.h"
#include "ui_addcategorydialog.h"

#include <QMessageBox>
#include <QPushButton>
///CONSTRUCTORS///
AddCategoryDialog::AddCategoryDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager) :
    QDialog(parent),
    ui(new Ui::AddCategoryDialog),
    mCategoryManager(categoryManager){
    ui->setupUi(this);
    ui->uButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);


    connect(this->ui->uButtonBox, SIGNAL(accepted()), this, SLOT(addCategory()));
    //TODO change textedit to lineedit, or figure out how to signal
    connect(this->ui->uTitleForm, SIGNAL(textEdited(QString)), this, SLOT(updateTitle(QString)));
    connect(this->ui->uTagForm, SIGNAL(textEdited(QString)), this, SLOT(updateTag(QString)));
    connect(this->ui->uDescriptionForm, SIGNAL(textChanged()), this, SLOT(updateDescription()));
}

///DESTRUCTOR///
AddCategoryDialog::~AddCategoryDialog() {
    delete ui;
}

///SLOTS///
void AddCategoryDialog::addCategory() {
    mCategoryManager->addCategory(new Category(mTitle, mTag, mDescription));
}

void AddCategoryDialog::updateTitle(QString title) {
    mTitle = title;
    checkButtons();
}

void AddCategoryDialog::updateTag(QString tag) {
    mTag = tag;
    checkButtons();
}

void AddCategoryDialog::updateDescription() {
    mDescription = ui->uDescriptionForm->toPlainText();
}

///PRIVATE METHODS///
void AddCategoryDialog::checkButtons() {
    if (mTitle.isEmpty() || mTag.isEmpty()) {
        ui->uButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
    else {
        ui->uButtonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }
}
