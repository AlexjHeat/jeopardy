#ifndef EDITCATEGORYDIALOG_H
#define EDITCATEGORYDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include "categorymanager.h"

namespace Ui {
class EditCategoryDialog;
}

class EditCategoryDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit EditCategoryDialog(QWidget *parent, std::shared_ptr<CategoryManager> categoryManager);
        ~EditCategoryDialog();

    private:
        void clearEdits();
        bool isEdited();

        QStringListModel                    mCategoryListModel;
        std::shared_ptr<CategoryManager>    mCategoryManager;
        Category*                           mCurrentCategory;

        QString mEditedTitle;
        QString mEditedTag;
        QString mEditedDescription;
        bool edited;

        Ui::EditCategoryDialog              *ui;

    private slots:
        void updateTitle(QString title);
        void updateTag(QString tag);
        void updateDescription();
        void categoryDoubleClicked(QModelIndex index);
        void applyChanges();
};

#endif // EDITCATEGORYDIALOG_H
