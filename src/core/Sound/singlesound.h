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

#ifndef SINGLESOUND_H
#define SINGLESOUND_H
#include "Animators/eboxorsound.h"
#include "Animators/qrealanimator.h"
class FixedLenAnimationRect;
class SoundHandler;
class Samples;
class SoundReaderForMerger;
class SoundDataHandler;
class HddCachableCacheHandler;

class SingleSound : public eBoxOrSound {
    e_OBJECT
    Q_OBJECT
protected:
    SingleSound(const qsptr<FixedLenAnimationRect> &durRect = nullptr);
public:
    bool SWT_isSound() const { return true; }
    bool SWT_isSingleSound() const { return mIndependent; }

    void setupTreeViewMenu(PropertyMenu * const menu);

    int prp_getRelFrameShift() const;

    QMimeData *SWT_createMimeData() {
        if(!mIndependent) return nullptr;
        return eBoxOrSound::SWT_createMimeData();
    }

    bool SWT_shouldBeVisible(const SWT_RulesCollection &rules,
                             const bool parentSatisfies,
                             const bool parentMainTarget) const;

    void writeProperty(eWriteStream& dst) const;
    void readProperty(eReadStream& src);

    void setFilePath(const QString &path);

    qreal getVolumeAtRelFrame(const qreal relFrame) const {
        return mVolumeAnimator->getEffectiveValue(relFrame);
    }

    SoundReaderForMerger * getSecondReader(const int relSecondId);

    stdsptr<Samples> getSamplesForSecond(const int relSecondId);

    int getSampleShift() const;
    SampleRange relSampleRange() const;
    SampleRange absSampleRange() const;
    iValueRange absSecondToRelSeconds(const int absSecond);

    const HddCachableCacheHandler* getCacheHandler() const;

    bool videoSound() const {
        return !mIndependent;
    }

    void setStretch(const qreal stretch);
    qreal getStretch() const { return mStretch; }
    QrealSnapshot getVolumeSnap() const;

    bool isEnabled() const {
        return mEnabled;
    }

    void setEnabled(const bool enable) {
        if(enable == mEnabled) return;
        mEnabled = enable;
        SWT_setDisabled(!mEnabled);
        prp_afterWholeInfluenceRangeChanged();
    }
    void setSoundDataHandler(SoundDataHandler * const newDataHandler);
private:
    iValueRange absSecondToRelSecondsAbsStretch(const int absSecond);
    void updateDurationRectLength();

    qreal getCanvasFPS() const;
    const bool mIndependent;

    bool mEnabled = true;
    qreal mStretch = 1;
    stdsptr<SoundHandler> mCacheHandler;

    qsptr<QrealAnimator> mVolumeAnimator =
            enve::make_shared<QrealAnimator>(100, 0, 200, 1, "volume");
};

#endif // SINGLESOUND_H