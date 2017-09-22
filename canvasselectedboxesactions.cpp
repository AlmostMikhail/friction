#include "canvas.h"
#include "mainwindow.h"
#include "pathpivot.h"

int Canvas::nextRelFrameWithKey(const int &relFrame) {
    int minNextFrame = INT_MAX;
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        int boxRelFrame = box->prp_absFrameToRelFrame(relFrame);
        int boxNext = box->prp_nextRelFrameWithKey(boxRelFrame);
        int absNext = box->prp_relFrameToAbsFrame(boxNext);
        if(minNextFrame > absNext) {
            minNextFrame = absNext;
        }
    }
    if(minNextFrame == INT_MAX) {
        return relFrame;
    }
    return minNextFrame;
}

int Canvas::prevRelFrameWithKey(const int &relFrame) {
    int maxPrevFrame = INT_MIN;
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        int boxRelFrame = box->prp_absFrameToRelFrame(relFrame);
        int boxPrev = box->prp_prevRelFrameWithKey(boxRelFrame);
        int absPrev = box->prp_relFrameToAbsFrame(boxPrev);
        if(maxPrevFrame < absPrev) {
            maxPrevFrame = absPrev;
        }
    }
    if(maxPrevFrame == INT_MIN) {
        return relFrame;
    }
    return maxPrevFrame;
}

void Canvas::convertSelectedBoxesToPath() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->objectToPath();
    }
}

void Canvas::convertSelectedPathStrokesToPath() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->strokeToPath();
    }
}

void Canvas::setSelectedFontFamilyAndStyle(QString family, QString style) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setSelectedFontFamilyAndStyle(family, style);
    }
}

void Canvas::setSelectedFontSize(qreal size) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setSelectedFontSize(size);
    }
}

void Canvas::applyBlurToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new BlurEffect());
    }
}

void Canvas::applyShadowToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new ShadowEffect());
    }
}

void Canvas::applyBrushEffectToSelected() {
    //Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        //box->addEffect(new BrushEffect());
    //}
}

void Canvas::applyLinesEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new LinesEffect());
    }
}

void Canvas::applyCirclesEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new CirclesEffect());
    }
}

void Canvas::applySwirlEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new SwirlEffect());
    }
}

void Canvas::applyOilEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new OilEffect());
    }
}

void Canvas::applyImplodeEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new ImplodeEffect());
    }
}

void Canvas::applyDesaturateEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new DesaturateEffect());
    }
}

void Canvas::applyReplaceColorEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new ReplaceColorEffect());
    }
}

void Canvas::applyColorizeEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->addEffect(new ColorizeEffect());
    }
}

#include "PathEffects/patheffect.h"
void Canvas::applyDiscretePathEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(!box->SWT_isPathBox()) continue;
        box->addPathEffect(new DisplacePathEffect());
    }
}

void Canvas::applyDuplicatePathEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(!box->SWT_isPathBox()) continue;
        box->addPathEffect(new DuplicatePathEffect());
    }
}

void Canvas::applyDiscreteOutlinePathEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(!box->SWT_isPathBox()) continue;
        box->addOutlinePathEffect(new DisplacePathEffect());
    }
}

void Canvas::applySumPathEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(!box->SWT_isPathBox()) continue;
        box->addPathEffect(new SumPathEffect((PathBox*)box));
    }
}

void Canvas::applyDuplicateOutlinePathEffectToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(!box->SWT_isPathBox()) continue;
        box->addOutlinePathEffect(new DuplicatePathEffect());
    }
}

void Canvas::resetSelectedTranslation() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->resetTranslation();
    }
}

void Canvas::resetSelectedScale() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->resetScale();
    }
}

void Canvas::resetSelectedRotation() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->resetRotation();
    }
}

NodePoint *Canvas::createNewPointOnLineNearSelected(
                        const QPointF &absPos,
                        const bool &adjust,
                        const qreal &canvasScaleInv) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        NodePoint *point = box->createNewPointOnLineNear(absPos, adjust,
                                                         canvasScaleInv);
        if(point != NULL) {
            return point;
        }
    }
    return NULL;
}

void Canvas::setDisplayedFillStrokeSettingsFromLastSelected() {
    if(mSelectedBoxes.isEmpty()) {
        mFillStrokeSettingsWidget->setCurrentSettings(NULL,
                                                      NULL);
    } else {
        setCurrentFillStrokeSettingsFromBox(mSelectedBoxes.last() );
    }
}


void Canvas::applyPaintSettingToSelected(
        const PaintSetting &setting) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->applyPaintSetting(setting);
    }
}

void Canvas::setSelectedFillColorMode(const ColorMode &mode) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setFillColorMode(mode);
    }
}

void Canvas::setSelectedStrokeColorMode(const ColorMode &mode) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setStrokeColorMode(mode);
    }
}

void Canvas::setSelectedCapStyle(Qt::PenCapStyle capStyle) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setStrokeCapStyle(capStyle);
    }
}

void Canvas::setSelectedJoinStyle(Qt::PenJoinStyle joinStyle) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setStrokeJoinStyle(joinStyle);
    }
}

void Canvas::setSelectedStrokeWidth(qreal strokeWidth, const bool &finish) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->setStrokeWidth(strokeWidth, finish);
    }
}

void Canvas::startSelectedStrokeWidthTransform() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->startSelectedStrokeWidthTransform();
    }
}

void Canvas::startSelectedStrokeColorTransform() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->startSelectedStrokeColorTransform();
    }
}

void Canvas::startSelectedFillColorTransform() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->startSelectedFillColorTransform();
    }
}

VectorPathEdge *Canvas::getEdgeAt(QPointF absPos) {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(box->isSelected() ) {
            VectorPathEdge *pathEdge = box->getEdge(absPos,
                                                    1./mCanvasTransformMatrix.m11());
            if(pathEdge == NULL) continue;
            return pathEdge;
        }
    }
    return NULL;
}

void Canvas::rotateSelectedBoxesStartAndFinish(const qreal &rotBy) {
    if(mLocalPivot) {
        Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
            box->startRotTransform();
            box->rotateBy(rotBy);
            box->finishTransform();
        }
    } else {
        Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
            box->startRotTransform();
            box->startPosTransform();
            box->saveTransformPivotAbsPos(mRotPivot->getAbsolutePos());
            box->rotateRelativeToSavedPivot(rotBy);
            box->finishTransform();
        }
    }
}

void Canvas::rotateSelectedBy(const qreal &rotBy,
                              const QPointF &absOrigin,
                              const bool &startTrans) {
    if(mLocalPivot) {
        if(startTrans) {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->startRotTransform();
                box->rotateBy(rotBy);
            }
        } else {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->rotateBy(rotBy);
            }
        }
    } else {
        if(startTrans) {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->startRotTransform();
                box->startPosTransform();
                box->saveTransformPivotAbsPos(absOrigin);
                box->rotateRelativeToSavedPivot(rotBy);
            }
        } else {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->rotateRelativeToSavedPivot(rotBy);
            }
        }
    }
}

void Canvas::scaleSelectedBy(qreal scaleBy,
                             QPointF absOrigin,
                             bool startTrans) {
    scaleSelectedBy(scaleBy, scaleBy,
                    absOrigin, startTrans);
}

void Canvas::scaleSelectedBy(qreal scaleXBy, qreal scaleYBy,
                                 QPointF absOrigin,
                                 bool startTrans) {
    if(mLocalPivot) {
        if(startTrans) {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->startScaleTransform();
                box->scale(scaleXBy, scaleYBy);
            }
        } else {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->scale(scaleXBy, scaleYBy);
            }
        }
    } else {
        if(startTrans) {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->startScaleTransform();
                box->startPosTransform();
                box->saveTransformPivotAbsPos(absOrigin);
                box->scaleRelativeToSavedPivot(scaleXBy,
                                               scaleYBy);
            }
        } else {
            Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
                box->scaleRelativeToSavedPivot(scaleXBy,
                                               scaleYBy);
            }
        }
    }
}

QPointF Canvas::getSelectedBoxesAbsPivotPos() {
    if(mSelectedBoxes.isEmpty()) return QPointF(0., 0.);
    QPointF posSum = QPointF(0., 0.);
    int count = mSelectedBoxes.length();
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        posSum += box->getPivotAbsPos();
    }
    return posSum/count;
}

bool Canvas::isSelectionEmpty() {
    return mSelectedBoxes.isEmpty();
}

void Canvas::ungroupSelectedBoxes() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(box->SWT_isBoxesGroup()) {
            ((BoxesGroup*) box)->ungroup();
        }
    }
}

void Canvas::centerPivotForSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->centerPivotPosition(true);
    }
}

void Canvas::removeSelectedBoxesAndClearList() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        //box->deselect();
        box->removeFromParent();
    }
    mSelectedBoxes.clear(); schedulePivotUpdate();
}

void Canvas::addBoxToSelection(BoundingBox *box) {
    if(box->isSelected()) {
        return;
    }
    box->select();
    mSelectedBoxes.append(box); schedulePivotUpdate();
    sortSelectedBoxesByZAscending();
    //setCurrentFillStrokeSettingsFromBox(box);
    mMainWindow->setCurrentBox(box);
}

void Canvas::removeBoxFromSelection(BoundingBox *box) {
    box->deselect();
    mSelectedBoxes.removeOne(box); schedulePivotUpdate();
    if(mSelectedBoxes.isEmpty()) {
        mMainWindow->setCurrentBox(NULL);
    } else {
        mMainWindow->setCurrentBox(mSelectedBoxes.last());
    }
}

void Canvas::clearBoxesSelection() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->deselect();
    }
    mSelectedBoxes.clear(); schedulePivotUpdate();
    mMainWindow->setCurrentBox(NULL);
//    if(mLastPressedBox != NULL) {
//        mLastPressedBox->deselect();
//        mLastPressedBox = NULL;
//    }
}


void Canvas::applyCurrentTransformationToSelected() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->applyCurrentTransformation();
    }
}

bool zLessThan(BoundingBox *box1, BoundingBox *box2) {
    return box1->getZIndex() > box2->getZIndex();
}

void Canvas::sortSelectedBoxesByZAscending() {
    qSort(mSelectedBoxes.begin(), mSelectedBoxes.end(), zLessThan);
}

void Canvas::raiseSelectedBoxesToTop() {
    BoundingBox *box;
    Q_FOREACHInverted(box, mSelectedBoxes) {
        box->bringToFront();
    }
}

void Canvas::lowerSelectedBoxesToBottom() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->bringToEnd();
    }
}

void Canvas::lowerSelectedBoxes() {
    BoundingBox *box;
    int lastZ = -10000;
    bool lastBoxChanged = true;
    Q_FOREACHInverted(box, mSelectedBoxes) {
        int boxZ = box->getZIndex();
        if(boxZ - 1 != lastZ || lastBoxChanged) {
            box->moveDown();
        }
        lastZ = boxZ;
        lastBoxChanged = boxZ - box->getZIndex() != 0;
    }
}

void Canvas::raiseSelectedBoxes() {
    int lastZ = -10000;
    bool lastBoxChanged = true;
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        int boxZ = box->getZIndex();
        if(boxZ + 1 != lastZ || lastBoxChanged) {
            box->moveUp();
        }
        lastZ = boxZ;
        lastBoxChanged = boxZ - box->getZIndex() != 0;
    }
}

void Canvas::deselectAllBoxes() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        removeBoxFromSelection(box);
    }
}
#include "pathpivot.h"
MovablePoint *Canvas::getPointAtAbsPos(const QPointF &absPos,
                                 const CanvasMode &currentMode,
                                 const qreal &canvasScaleInv) {
    if(currentMode == MOVE_POINT ||
       currentMode == ADD_POINT ||
       currentMode == MOVE_PATH) {
        if(mRotPivot->isPointAtAbsPos(absPos, canvasScaleInv)) {
            return mRotPivot;
        }
        MovablePoint *pointAtPos = NULL;
        Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
            pointAtPos = box->getPointAtAbsPos(absPos,
                                               currentMode,
                                               canvasScaleInv);
            if(pointAtPos != NULL) {
                break;
            }
        }
        return pointAtPos;
    }
    return NULL;
}

void Canvas::finishSelectedBoxesTransform() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->finishTransform();
    }
}

void Canvas::cancelSelectedBoxesTransform() {
    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        box->cancelTransform();
    }
}

void Canvas::moveSelectedBoxesByAbs(const QPointF &by,
                                    const bool &startTransform) {
    if(startTransform) {
        Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
            box->startPosTransform();
            box->moveByAbs(by);
        }
    } else {
        Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
            box->moveByAbs(by);
        }
    }
}

//QPointF BoxesGroup::getRelCenterPosition() {
//    QPointF posSum = QPointF(0., 0.);
//    if(mChildren.isEmpty()) return posSum;
//    int count = mChildren.length();
//    Q_FOREACH(BoundingBox *box, mChildren) {
//        posSum += box->getPivotAbsPos();
//    }
//    return mapAbsPosToRel(posSum/count);
//}

#include "Boxes/linkbox.h"
void Canvas::createLinkBoxForSelected() {
    Q_FOREACH(BoundingBox *selectedBox, mSelectedBoxes) {
        mCurrentBoxesGroup->addChild(selectedBox->createLink());
    }
}

void Canvas::duplicateSelectedBoxes() {
    Q_FOREACH(BoundingBox *selectedBox, mSelectedBoxes) {
        selectedBox->createDuplicateWithSameParent();
    }
}

void Canvas::groupSelectedBoxes() {
    if(mSelectedBoxes.count() == 0) return;
    BoxesGroup *newGroup = new BoxesGroup();
    BoundingBox *box;
    Q_FOREACHInverted(box, mSelectedBoxes) {
        box->removeFromParent();
        newGroup->addChild(box);
    }
    mSelectedBoxes.clear(); schedulePivotUpdate();
    mCurrentBoxesGroup->addChild(newGroup);
    addBoxToSelection(newGroup);
}

#include "pathoperations.h"
VectorPath *Canvas::getPathResultingFromOperation(
                                const bool &unionInterThis,
                                const bool &unionInterOther) {
    VectorPath *newPath = new VectorPath();
    FullVectorPath *targetPath = new FullVectorPath();
    FullVectorPath *addToPath = NULL;
    FullVectorPath *addedPath = NULL;

    Q_FOREACH(BoundingBox *box, mSelectedBoxes) {
        if(box->SWT_isPathBox()) {
            SkPath boxPath = ((PathBox*)box)->getRelativePath();
            boxPath.transform(QMatrixToSkMatrix(box->getRelativeTransform()));
            addToPath = targetPath;
            addToPath->generateSinglePathPaths();
            addedPath = new FullVectorPath();
            addedPath->generateFromPath(boxPath);
            addToPath->intersectWith(addedPath,
                                     unionInterThis,
                                     unionInterOther);
            targetPath = new FullVectorPath();
            targetPath->getSeparatePathsFromOther(addToPath);
            targetPath->getSeparatePathsFromOther(addedPath);

            delete addedPath;
            delete addToPath;
        }
    }

    targetPath->addAllToVectorPath(newPath->getPathAnimator());
    mCurrentBoxesGroup->addChild(newPath);
    return newPath;
}

void Canvas::selectedPathsDifference() {
    VectorPath *newPath = getPathResultingFromOperation(false,
                                                        true);

    clearBoxesSelection();
    addBoxToSelection(newPath);
}

void Canvas::selectedPathsIntersection() {
    VectorPath *newPath = getPathResultingFromOperation(false,
                                                        false);

    clearBoxesSelection();
    addBoxToSelection(newPath);
}

void Canvas::selectedPathsDivision() {
    VectorPath *newPath1 = getPathResultingFromOperation(false,
                                                        false);

    VectorPath *newPath2 = getPathResultingFromOperation(false,
                                                        true);

    clearBoxesSelection();
    addBoxToSelection(newPath1);
    addBoxToSelection(newPath2);
}

void Canvas::selectedPathsExclusion() {
    VectorPath *newPath1 = getPathResultingFromOperation(false,
                                                         true);
    VectorPath *newPath2 = getPathResultingFromOperation(true,
                                                         false);

    clearBoxesSelection();
    addBoxToSelection(newPath1);
    addBoxToSelection(newPath2);
}

void Canvas::selectedPathsUnion() {
    VectorPath *newPath = getPathResultingFromOperation(true,
                                                        true);

    clearBoxesSelection();
    addBoxToSelection(newPath);
}
