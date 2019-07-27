#include "boxtargetwidget.h"
#include <QMimeData>
#include <QPainter>
#include <QMenu>
#include "Boxes/containerbox.h"
#include "Properties/boxtargetproperty.h"
#include "GUI/mainwindow.h"

BoxTargetWidget::BoxTargetWidget(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true);
    setMaximumWidth(150);
}

void BoxTargetWidget::setTargetProperty(BoxTargetProperty *property) {
    mProperty = property;
    update();
}

void BoxTargetWidget::dropEvent(QDropEvent *event) {
    if(BoundingBoxMimeData::hasFormat(event->mimeData())) {
        auto boxMimeData = static_cast<
                const BoundingBoxMimeData*>(event->mimeData());
        BoundingBox *targetT = boxMimeData->getTarget();
        mProperty->setTarget(targetT);
        mDragging = false;
        update();
        Document::sInstance->actionFinished();
    }
}

void BoxTargetWidget::dragEnterEvent(QDragEnterEvent *event) {
    if(BoundingBoxMimeData::hasFormat(event->mimeData())) {
        auto boxMimeData = static_cast<
                const BoundingBoxMimeData*>(event->mimeData());
        BoundingBox *targetT = boxMimeData->getTarget();
        const auto tester = [](Property * prop) {
            return prop->SWT_isBoundingBox();
        };
        const auto parentBox = mProperty->getFirstAncestor<BoundingBox>(tester);
        Q_ASSERT(parentBox);
        Q_ASSERT(targetT);
        if(parentBox == targetT) return;
        if(parentBox->getParentGroup() != targetT->getParentGroup()) return;
        event->acceptProposedAction();
        mDragging = true;
        update();
    }
}

void BoxTargetWidget::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void BoxTargetWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    mDragging = false;
    update();
    event->accept();
}

void BoxTargetWidget::mousePressEvent(QMouseEvent *event) {
    if(!mProperty) return;
    if(event->button() == Qt::LeftButton) {
        auto tester = &Property::SWT_isBoundingBox;
        BoundingBox *parentBox =
                mProperty->getFirstAncestor<BoundingBox>(tester);
        if(!parentBox) return;
        const auto srcGroup = parentBox->getParentGroup();
        if(!srcGroup) return;
        const auto& boxesT = srcGroup->getContainedBoxes();
        QMenu menu(this);


        BoundingBox *currentTarget = mProperty->getTarget();
        int i = -1;
        QAction *act = menu.addAction("-none-");
        if(!currentTarget) {
            act->setCheckable(true);
            act->setChecked(true);
            act->setDisabled(true);
        }
        for(const auto& boxT : boxesT) {
            i++;
            if(boxT.data() == parentBox) continue;
            QAction *act2 = menu.addAction(boxT->prp_getName());
            act2->setProperty("targetBoxPtr", i);
            if(currentTarget == boxT.data()) {
                act2->setCheckable(true);
                act2->setChecked(true);
                act2->setDisabled(true);
            }
        }
        QAction *selected_action = menu.exec(mapToGlobal(QPoint(0, height())));
        if(selected_action != nullptr) {
            QVariant varT = selected_action->property("targetBoxPtr");
            if(varT.isValid()) {
                mProperty->setTarget(boxesT.at(varT.toInt()).data());
            } else {
                mProperty->setTarget(nullptr);
            }
            Document::sInstance->actionFinished();
        } else {

        }
    } else if(event->button() == Qt::RightButton) {

    }
}

void BoxTargetWidget::paintEvent(QPaintEvent *) {
    if(!mProperty) return;
    QPainter p(this);
    if(mProperty->SWT_isDisabled()) p.setOpacity(.5);
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(Qt::white);
    if(mDragging) {
        p.setPen(Qt::white);
    } else {
        p.setPen(Qt::black);
    }
    p.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 5., 5.);

    p.setPen(Qt::black);
    if(mProperty) {
        BoundingBox *target = mProperty->getTarget();
        if(!target) {
            p.drawText(rect(), Qt::AlignCenter, "-none-");
        } else {
            p.drawText(rect(), Qt::AlignCenter, target->prp_getName());
        }
    }

    p.end();
}