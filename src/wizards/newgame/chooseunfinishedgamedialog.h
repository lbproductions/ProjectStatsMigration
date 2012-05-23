#ifndef CHOOSEUNFINISHEDGAMEDIALOG_H
#define CHOOSEUNFINISHEDGAMEDIALOG_H

#include <QDialog>

class QListWidgetItem;

namespace Ui {
    class ChooseUnfinishedGameDialog;
}

class Player;

namespace Wizards {

namespace NewGame {

class ChooseUnfinishedGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseUnfinishedGameDialog(QList<Player*> list, QWidget *parent = 0);
    ~ChooseUnfinishedGameDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ChooseUnfinishedGameDialog *ui;
};

}
}

#endif // CHOOSEUNFINISHEDGAMEDIALOG_H
