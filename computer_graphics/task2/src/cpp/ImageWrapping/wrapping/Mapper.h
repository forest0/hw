#ifndef MAPPER_H
#define MAPPER_H

#include <QtCore/QPoint>
#include <vector>

class Mapper
{
    public:
        explicit Mapper();

        virtual ~Mapper();
        virtual QPoint map(const QPoint &point) const = 0;

};

#endif // MAPPER_H
