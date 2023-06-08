/*
#
# Friction - https://friction2d.com
#
# Copyright (c) Friction contributors
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# See 'README.md' for more information.
#
*/

// Fork of enve - Copyright (C) 2016-2020 Maurycy Liebner

#ifndef BOXESLISTANIMATIONDOCKWIDGET_H
#define BOXESLISTANIMATIONDOCKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <qscrollarea.h>
#include <QScrollArea>
#include <QApplication>
#include <QScrollBar>
#include <QComboBox>
#include <QMenuBar>
#include <QLineEdit>
#include <QWidgetAction>
#include <QToolBar>
#include <QStackedWidget>

#include "smartPointers/ememory.h"
#include "framerange.h"
#include "timelinebasewrappernode.h"
#include "triggerlabel.h"
#include "qdoubleslider.h"
#include "fontswidget.h"

class FrameScrollBar;
class TimelineWidget;
class MainWindow;
class AnimationDockWidget;
class RenderWidget;
class ActionButton;
class Canvas;
class Document;
class LayoutHandler;
class SwitchButton;
class BrushContexedWrapper;
class FontsWidget;

enum class CanvasMode : short;

class TimelineDockWidget : public QWidget
{
public:
    explicit TimelineDockWidget(Document &document,
                                LayoutHandler* const layoutH,
                                MainWindow * const parent,
                                FontsWidget *fontwidget = nullptr);
    bool processKeyPress(QKeyEvent *event);
    void previewFinished();
    void previewBeingPlayed();
    void previewBeingRendered();
    void previewPaused();

    void updateSettingsForCurrentCanvas(Canvas * const canvas);

private:
    void setResolutionText(QString text);

    void setLoop(const bool loop);
    void interruptPreview();

    void setLocalPivot(const bool local);

    void playPreview();
    void renderPreview();
    void pausePreview();
    void resumePreview();

    void updateButtonsVisibility(const CanvasMode mode);

    void setupDrawPathSpins();

    //void setBrushColor(const QColor& color);
    //void setBrush(BrushContexedWrapper* const brush);

    Document& mDocument;
    MainWindow* const mMainWindow;
    QStackedWidget* const mTimelineLayout;

    QToolBar *mToolBar;

    QVBoxLayout *mMainLayout;
    QComboBox *mResolutionComboBox;

    QAction *mPlayFromBeginningButton;
    QAction *mPlayButton;
    QAction *mStopButton;
    QAction *mLoopButton;

    QAction* mLocalPivotAct;
    SwitchButton *mLocalPivot;
    QAction* mNodeVisibilityAct;
    SwitchButton *mNodeVisibility;

    SwitchButton* mDrawPathAuto;
    QAction* mDrawPathAutoAct;
    QDoubleSlider* mDrawPathSmooth;
    QAction* mDrawPathSmoothAct;
    QDoubleSlider* mDrawPathMaxError;
    QAction* mDrawPathMaxErrorAct;

    QList<TimelineWidget*> mTimelineWidgets;
    AnimationDockWidget *mAnimationDockWidget;
    FontsWidget *mFontWidget;
};

#endif // BOXESLISTANIMATIONDOCKWIDGET_H
