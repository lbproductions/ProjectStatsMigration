#ifndef NEWROUNDDIALOG_H
#define NEWROUNDDIALOG_H

#include <QDialog>

namespace Ui {
class NewRoundDialog;
}

class DoppelkopfRound;

class NewRoundDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewRoundDialog(QWidget *parent = 0);
    ~NewRoundDialog();
    
    void setDoppelkopfRound(DoppelkopfRound *round);

private slots:
    void setCurrentPage(int);

    void checkNormalRoundContents();
    void checkHochzeitRoundContents();
    void checkSoloRoundContents();
    void checkTrumpfabgabeRoundContents();

    void save();
    void saveNormalRound();
    void saveHochzeitRound();
    void saveSoloRound();
    void saveTrumpfabgabeRound();

private:
    Ui::NewRoundDialog *ui;
    DoppelkopfRound *m_doppelkopfRound;
};

#endif // NEWROUNDDIALOG_H
