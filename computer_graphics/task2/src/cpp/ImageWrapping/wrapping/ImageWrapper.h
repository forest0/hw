#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <QtCore/QObject>
#include "Mapper.h"

class ImageWrapper : public QObject {
    Q_OBJECT
    public:
        explicit ImageWrapper(Mapper *mapper, QObject *parent = nullptr);
        ~ImageWrapper();
        QImage * wrap(QImage *image) const;

    signals:

    public slots:

    private:
        Mapper *mapper;
};

#endif // IMAGEWRAPPER_H
