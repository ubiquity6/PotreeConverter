

#ifndef POINTREADER_H
#define POINTREADER_H

#include <boost/filesystem.hpp>

#include "Point.h"
#include "AABB.h"

namespace fs = boost::filesystem;

namespace Potree{

class PointReader{
public:

	virtual ~PointReader(){};

	virtual bool readNextPoint() = 0;

	virtual Point getPoint() = 0;

	virtual AABB getAABB() = 0;

	virtual long long numPoints() = 0;

	virtual void close() = 0;
};

}

#endif
