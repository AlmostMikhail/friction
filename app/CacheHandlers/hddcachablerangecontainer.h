#ifndef HDDCACHABLERANGECONTAINER_H
#define HDDCACHABLERANGECONTAINER_H
#include "hddcachablecontainer.h"
#include "tmpfilehandlers.h"
#include "framerange.h"
class _ScheduledTask;
class HDDCachableCacheHandler;

class HDDCachableRangeContainer : public HDDCachable {
    friend class SoundContainerTmpFileDataSaver;
protected:
    HDDCachableRangeContainer(const FrameRange &range,
                              HDDCachableCacheHandler * const parent) :
        mRange(range), mParentCacheHandler_k(parent) {}
    virtual int clearMemory() = 0;
public:
    int freeAndRemove_k();

    int getRangeMin() const;
    const FrameRange& getRange() const {
        return mRange;
    }
    int getRangeMax() const;
    int rangeSpan() const {
        return mRange.span();
    }

    void setUnaryRange(const int &unary);
    void setRangeMax(const int &max);
    void setRangeMin(const int &min);
    void setRange(const FrameRange &range);
    bool inRange(const int &unary) const;
private:
    FrameRange mRange;
    HDDCachableCacheHandler * const mParentCacheHandler_k;
};

#endif // HDDCACHABLERANGECONTAINER_H
