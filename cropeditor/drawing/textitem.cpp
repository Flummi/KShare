#include "textitem.hpp"
#include <QInputDialog>
#include <QtMath>

bool TextItem::init(CropScene *s) {
    bool ok;
    s->hide();
    text = QInputDialog::getText(nullptr, "Text to add", "Input", QLineEdit::Normal, QString(), &ok);
    s->show();
    return ok;
}

void TextItem::mouseDragEvent(QGraphicsSceneMouseEvent *e, CropScene *scene) {
    if (!textItem) {
        textItem = scene->addSimpleText(text, scene->font());
        textItem->setPos(e->scenePos());
        textItem->setPen(scene->pen().color());
        textItem->setBrush(scene->pen().color());
    } else {
        auto ee
        = 180 + qRadiansToDegrees(qAtan2((textItem->pos().y() - e->scenePos().y()), (textItem->pos().x() - e->scenePos().x())));
        textItem->setRotation(ee);
    }
}

void TextItem::mouseDragEndEvent(QGraphicsSceneMouseEvent *, CropScene *) {
}

QString TextItem::name() {
    return "Text";
}
