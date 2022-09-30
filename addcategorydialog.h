#ifndef ADDCATEGORYDIALOG_H
#define ADDCATEGORYDIALOG_H

#include <QDialog>
#include "category.h"

#include "categorymanager.h"

namespace Ui {
class AddCategoryDialog;
}

class AddCategoryDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit AddCategoryDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager);
        ~AddCategoryDialog();

    public slots:
        void addCategory();
        void updateTitle(QString);
        void updateTag(QString);
        void updateDescription();

    private:
        void checkButtons();

        Ui::AddCategoryDialog *ui;

        QString mTitle;
        QString mTag;
        QString mDescription;

        std::shared_ptr<CategoryManager> mCategoryManager;
};

#endif // ADDCATEGORYDIALOG_H
