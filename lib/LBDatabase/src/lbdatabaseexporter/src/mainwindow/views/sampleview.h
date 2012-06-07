#ifndef MAINWINDOWNS_SAMPLEVIEW_H
#define MAINWINDOWNS_SAMPLEVIEW_H

#include <QWidget>

namespace MainWindowNS {

class SampleView : public QWidget
{
    Q_OBJECT
public:
    explicit SampleView(const QString &label, QWidget *parent = 0);

};

} // namespace MainWindowNS

#endif // MAINWINDOWNS_SAMPLEVIEW_H
