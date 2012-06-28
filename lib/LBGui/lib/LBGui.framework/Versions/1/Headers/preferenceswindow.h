#ifndef LBGUI_PREFERENCESWINDOW_H
#define LBGUI_PREFERENCESWINDOW_H

#include <QMainWindow>

namespace LBGui {

class PreferencesPage;

class PreferencesWindowPrivate;
class PreferencesWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PreferencesWindow(QWidget *parent = 0);
    ~PreferencesWindow();

    void addPage(PreferencesPage *page);
    void setCurrentPage(PreferencesPage *page);
    
private Q_SLOTS:
    void onPageSelected();

private:
    QScopedPointer<PreferencesWindowPrivate> d_ptr;
    Q_DECLARE_PRIVATE(PreferencesWindow)
    Q_DISABLE_COPY(PreferencesWindow)
};

} // namespace LBGui

#endif // LBGUI_PREFERENCESWINDOW_H
