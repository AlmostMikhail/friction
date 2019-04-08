#ifndef IMAGECACHEHANDLER_H
#define IMAGECACHEHANDLER_H
#include "skia/skiahelpers.h"
#include "filecachehandler.h"
class ImageCacheHandler;
class ImageLoader : public _HDDTask {
    friend class StdSelfRef;
protected:
    ImageLoader(const QString &filePath,
                ImageCacheHandler * const handler);
public:
    void _processUpdate();
    void afterProcessingFinished();
private:
    ImageCacheHandler * const mTargetHandler;
    const QString mFilePath;
    sk_sp<SkImage> mImage;
};

class ImageCacheHandler : public FileCacheHandler {
    friend class StdSelfRef;
    friend class ImageLoader;
protected:
    ImageCacheHandler(const QString &filePath);
public:
    void clearCache() {
        mImage.reset();
        FileCacheHandler::clearCache();
    }

    ImageLoader * scheduleLoad() {
        const auto loader = SPtrCreate(ImageLoader)(mFilePath, this);
        loader->scheduleTask();
        return loader.get();
    }

    bool hasImage() const {
        return mImage.get();
    }

    sk_sp<SkImage> getImage() { return mImage; }
    sk_sp<SkImage> getImageCopy() {
        return SkiaHelpers::makeSkImageCopy(mImage);
    }
protected:
    void setImage(const sk_sp<SkImage>& img) {
        mImage = img;
    }
private:
    sk_sp<SkImage> mImage;
};

#endif // IMAGECACHEHANDLER_H
