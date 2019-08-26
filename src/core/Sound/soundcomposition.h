// enve - 2D animations software
// Copyright (C) 2016-2019 Maurycy Liebner

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SOUNDCOMPOSITION_H
#define SOUNDCOMPOSITION_H

#include "Animators/dynamiccomplexanimator.h"
#include "CacheHandlers/hddcachablecachehandler.h"
#include "CacheHandlers/samples.h"
#include "singlesound.h"
#include "esoundsettings.h"
#include <math.h>

#include <QAudioOutput>
#include <QByteArray>
#include <QComboBox>
#include <QIODevice>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
class Canvas;
class SoundMerger;

class SoundComposition : public QIODevice {
public:
    SoundComposition(Canvas * const parent);

    void start(const int startFrame);
    void stop();

    qint64 readData(char *data, qint64 maxLen);
    qint64 writeData(const char *data, qint64 len);

    void addSound(const qsptr<SingleSound> &sound);
    void removeSound(const qsptr<SingleSound> &sound);

    void secondFinished(const int secondId,
                        const stdsptr<Samples>& samples);

    void startBlockingAtFrame(const int frame);
    void blockUpToFrame(const int frame);

    void unblockAll();

    void scheduleFrameRange(const FrameRange& range);
    SoundMerger * scheduleFrame(const int frameId);
    HddCachableCacheHandler& getCacheHandler() {
        return mSecondsCache;
    }

    bool hasAnySounds() const { return !mSounds.isEmpty(); }
private:
    SoundMerger * scheduleSecond(const int secondId);

    void frameRangeChanged(const FrameRange &range);

    void secondRangeChanged(const iValueRange &range) {
        mSecondsCache.remove(range);
    }

    eSoundSettingsData mSettings;
    iValueRange mBlockRange{0, -1};
    QList<int> mProcessingSeconds;
    const Canvas * const mParent;
    qint64 mPos;
    typedef DynamicComplexAnimator<SingleSound> ContType;
    qsptr<ContType> mSoundsContainer = enve::make_shared<ContType>("sounds");
    QList<qsptr<SingleSound>> mSounds;
    HddCachableCacheHandler mSecondsCache;
};

#endif // SOUNDCOMPOSITION_H