#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "categorymanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWindow; }
QT_END_NAMESPACE

class ControlWindow : public QMainWindow
{
    Q_OBJECT

    public:
        ControlWindow(QWidget *parent = nullptr);
        ~ControlWindow();

    public slots:
        bool categoryLoadAction();
        bool categorySaveAction();
        void categoryAddAction();
        void categoryRemoveAction();
        void categoryEditAction();
        void onExit();

        void categoryChanged(int);

    private:
        Ui::ControlWindow *ui;
        bool gameActive;
        std::shared_ptr<CategoryManager> mCategoryManager;

        //UI elements
        QList<QComboBox*>       mCategoryMenus;
        QList<QPushButton*>   mQuestionButtons;
        QList<QLabel*>          mCategoryDescriptions;
        QList<QPushButton*>     mQuestionEdit;

        //Helper Functions
        void editQuestion();
        void resetCategoryMenus();
        int getColumn(QObject* sender);

    private slots:
        void questionAction();


};
#endif // CONTROLWINDOW_H
