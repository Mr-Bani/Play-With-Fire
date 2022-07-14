#include "label.h"
#include <QFont>
#include <QTextDocument>
#include <QPainter>
#include "QStyleOptionGraphicsItem"
#include <QTextDocument>

label::label() {
    setDefaultTextColor("black");
    QFont f;
    f.setBold(true);
    f.setPixelSize(15);
    setFont(f);
    document()->setDocumentMargin(18);
}
