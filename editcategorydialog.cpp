#include "editcategorydialog.h"
#include "ui_editcategorydialog.h"
#include <QMessageBox>

///CONSTRUCTOR///
EditCategoryDialog::EditCategoryDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager) :
    QDialog(parent),
    mCategoryManager(categoryManager),
    edited(false),
    ui(new Ui::EditCategoryDialog) {

    ui->setupUi(this);

    mCategoryListModel.setStringList(mCategoryManager->getStringList());
    ui->uCategoryListView->setModel(&mCategoryListModel);
    ui->uCategoryListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->uCategoryListView->setAlternatingRowColors(true);
    //ui->uCategoryListView->setSelectionRectVisible(true);
    ui->uApplyButton->setDisabled(true);

    connect(this->ui->uTitleForm, SIGNAL(textEdited(QString)), this, SLOT(updateTitle(QString)));
    connect(this->ui->uTagForm, SIGNAL(textEdited(QString)), this, SLOT(updateTag(QString)));
    connect(this->ui->uDescriptionForm, SIGNAL(textChanged()), this, SLOT(updateDescription()));
    connect(this->ui->uCategoryListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(categoryDoubleClicked(QModelIndex)));
    connect(this->ui->uApplyButton, SIGNAL(clicked()), this, SLOT(applyChanges()));
}

///DESTRUCTOR///
EditCategoryDialog::~EditCategoryDialog() {
    delete ui;
}
///PRIVATE METHODS///
void EditCategoryDialog::clearEdits() {
    mEditedTitle = "";
    mEditedTag = "";
    mEditedDescription = "";
    edited = false;
}

///PRIVATE SLOTS///
void EditCategoryDialog::updateTitle(QString title) {
    mEditedTitle = title;
    if (mEditedTitle != "") {
        ui->uApplyButton->setDisabled(false);
    }
    edited = true;
}

void EditCategoryDialog::updateTag(QString tag) {
    mEditedTag = tag;
    if (mEditedTag != "") {
        ui->uApplyButton->setDisabled(false);
    }
    edited = true;
}

void EditCategoryDialog::updateDescription() {
    mEditedDescription = ui->uDescriptionForm->toPlainText();
    ui->uApplyButton->setDisabled(false);
    if (mEditedDescription != mCurrentCategory->getDescription()) {
        edited = true;
    }
}

void EditCategoryDialog::categoryDoubleClicked(QModelIndex index) {
    //Either saves or discards the edited info of the current category being edited
    if (edited) {
        bool reply = QMessageBox::question(this, "", "Apply Changes") == QMessageBox::Yes;
        if (reply) {
            applyChanges();
        }
        else {
            clearEdits();
        }
        edited = false;
    }

    int i = index.row();

    mEditedTitle = mCategoryManager->getTitle(i);
    mEditedTag = mCategoryManager->getTag(i);
    mEditedDescription = mCategoryManager->getDescription(i);
    ui->uTitleForm->setText(mEditedTitle);
    ui->uTagForm->setText(mEditedTag);
    ui->uDescriptionForm->setPlainText(mEditedDescription);

    ui->uApplyButton->setDisabled(true);
}

void EditCategoryDialog::applyChanges() {
    if (mEditedTitle == "" || mEditedTag == "") {
        QMessageBox::warning(nullptr, "Error", "Title and Tag must not be left blank");
        return;
    }
    //TODO implement way to make edits through CategoryManager
    mCurrentCategory->setTitle(mEditedTitle);
    mCurrentCategory->setTag(mEditedTag);
    mCurrentCategory->setDescription(mEditedDescription);

    edited = false;
    ui->uApplyButton->setDisabled(true);
    mCategoryListModel.setStringList(mCategoryManager->getStringList());

}
