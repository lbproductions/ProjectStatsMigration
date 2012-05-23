#ifndef LIVEDOKOGAMEOPTIONSWIDGET_H
#define LIVEDOKOGAMEOPTIONSWIDGET_H

#include <QWizardPage>

namespace Ui {
    class LiveDokoGameOptionsWidget;
}

namespace Wizards {

namespace NewGame {

class LiveDokoGameOptionsWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit LiveDokoGameOptionsWidget(QWidget *parent = 0);
    ~LiveDokoGameOptionsWidget();

    int nextId() const;

private slots:
    void on_checkBoxSolo_clicked(bool checked);
    void on_checkBoxSchmeisserei_clicked(bool checked);

private:
    Ui::LiveDokoGameOptionsWidget *ui;

    void saveOptions() const;
};

}
}

#endif // LIVEDOKOGAMEOPTIONSWIDGET_H
