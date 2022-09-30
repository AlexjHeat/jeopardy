#include "removecategorydialog.h"
#include "ui_removecategorydialog.h"

#include <QMessageBox>

///CONSTRUCTOR///
RemoveCategoryDialog::RemoveCategoryDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager) :
    QDialog(parent),
    ui(new Ui::RemoveCategoryDialog) {
    ui->setupUi(this);

    mCategoryManager = categoryManager;
    mCategoryListModel.setStringList(mCategoryManager->getStringList());
    ui->uCategoryListView->setModel(&mCategoryListModel);

    connect(this->ui->uRemoveButton, SIGNAL(clicked()), this, SLOT(removeCategory()));
    connect(this->ui->uUndoButton, SIGNAL(clicked()), this, SLOT(undoCategoryRemoval()));
}

///DESTRUCTOR///
RemoveCategoryDialog::~RemoveCategoryDialog() {
    delete ui;
}

///PUBLIC METHODS///
void RemoveCategoryDialog::resetCategoryTitleList() {
    mCategoryListModel.setStringList(mCategoryManager->getStringList());
    ui->uCategoryListView->setModel(&mCategoryListModel);
}

///SLOTS///
void RemoveCategoryDialog::removeCategory() {
    int i = ui->uCategoryListView->currentIndex().row();
    if (i < 0 || i >= mCategoryManager->count()) {
        QMessageBox::warning(this, "Error", "No category selected");
        return;
    }
    //TODO Fix message to display full title, tag, description
    QString msg = mCategoryManager->getTitle(i) + mCategoryManager->getDescription(i);
    bool reply = QMessageBox::question(this, "Remove category", msg) == QMessageBox::Yes;
    if (reply) {
        resetCategoryTitleList();
        mRemovedCategories.append(mCategoryManager->getCategory(i));
        mCategoryManager->removeCategory(i);
    }
    resetCategoryTitleList();
}

void RemoveCategoryDialog::undoCategoryRemoval() {
    for (int i = 0; i < mRemovedCategories.length(); i++) {
        mCategoryManager->addCategory(mRemovedCategories[i]);
    }
    mRemovedCategories.clear();
    resetCategoryTitleList();
}
