#ifndef LBGUI_PREFERENCESPAGE_H
#define LBGUI_PREFERENCESPAGE_H

#include <QWidget>

class QAction;

namespace LBGui {

class PreferencesWindow;

class PreferencesPagePrivate;
class PreferencesPage : public QWidget
{
    Q_OBJECT
public:
    explicit PreferencesPage(PreferencesWindow *parent);
    ~PreferencesPage();
    
    QString name() const;
    void setName(const QString &name);
    void setIcon(const QIcon &icon);

Q_SIGNALS:
    void selected();

private:
    friend class PreferencesWindowPrivate;

    QAction *action() const;

    QScopedPointer<PreferencesPagePrivate> d_ptr;
    Q_DECLARE_PRIVATE(PreferencesPage)
    Q_DISABLE_COPY(PreferencesPage)
};

} // namespace LBGui

#endif // LBGUI_PREFERENCESPAGE_H
