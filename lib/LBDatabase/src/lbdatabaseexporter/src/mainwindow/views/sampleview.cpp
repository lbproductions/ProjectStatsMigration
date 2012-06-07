#include "sampleview.h"

#include <QHBoxLayout>
#include <QLabel>

namespace MainWindowNS {

SampleView::SampleView(const QString &label, QWidget *parent) :
    QWidget(parent)
{
    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new QLabel(label));
    setLayout(layout);
}

} // namespace MainWindowNS
