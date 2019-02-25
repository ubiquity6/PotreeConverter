

#ifndef POINTREADER_H
#define POINTREADER_H

#ifdef USE_BOOST
#include <boost/filesystem.hpp>
#else
#include <experimental/filesystem>
#endif

#include "Point.h"
#include "AABB.h"

#ifdef USE_BOOST
namespace fs = boost::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

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
