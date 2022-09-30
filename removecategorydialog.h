#ifndef REMOVECATEGORYDIALOG_H
#define REMOVECATEGORYDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include "categorymanager.h"

namespace Ui {
class RemoveCategoryDialog;
}

class RemoveCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    RemoveCategoryDialog(QWidget *parent,  std::shared_ptr<CategoryManager> categoryManager);
    ~RemoveCategoryDialog();
    void resetCategoryTitleList();

public slots:
    void removeCategory();
    void undoCategoryRemoval();

private:
    QStringListModel mCategoryListModel;
    std::shared_ptr<CategoryManager> mCategoryManager;
    QList<Category*> mRemovedCategories;

    Ui::RemoveCategoryDialog *ui;
};

#endif // REMOVECATEGORYDIALOG_H
