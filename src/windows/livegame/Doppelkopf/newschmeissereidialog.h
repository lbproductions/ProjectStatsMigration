#ifndef DOKOLIVEGAMEWINDOWNS_NEWSCHMEISSEREIDIALOG_H
#define DOKOLIVEGAMEWINDOWNS_NEWSCHMEISSEREIDIALOG_H

#include <QDialog>

class DoppelkopfRound;

namespace DokoLiveGameWindowNS {

namespace Ui {
class NewSchmeissereiDialog;
}

class NewSchmeissereiDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewSchmeissereiDialog(QWidget *parent = 0);
    ~NewSchmeissereiDialog();

    void setDoppelkopfRound(DoppelkopfRound *round);

private slots:
    void on_buttonBox_accepted();

    void on_comboBoxPlayer_currentIndexChanged(int index);

private:
    Ui::NewSchmeissereiDialog *ui;
    DoppelkopfRound *m_round;
};


} // namespace DokoLiveGameWindowNS
#endif // DOKOLIVEGAMEWINDOWNS_NEWSCHMEISSEREIDIALOG_H
