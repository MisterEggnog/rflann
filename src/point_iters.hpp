#ifndef SRC_POINT_ITERS_HPP
#define SRC_POINT_ITERS_HPP

#include "point_cloud.hpp"

class PointBufIter {
	std::vector<Point>::const_iterator curr_, end_;
public:
	PointBufIter(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end);

	bool next(int64_t& x, int64_t& y, int64_t& z);
};

class NearestPointIter {
	// TO DO
public:
	bool next(int64_t& x, int64_t& y, int64_t& z);
};

struct PointCloudIter {
	union {
		PointBufIter points;
		NearestPointIter nearests;
	};
	enum {
		buf_iter,
		nearest,
	} type;

	~PointCloudIter() {
		switch (type) {
			case buf_iter: points.~PointBufIter();
			break;
			case nearest: nearests.~NearestPointIter();
			break;
		}
	}

	PointCloudIter(PointBufIter&& buf) {
		points = std::move(buf);
		type   = buf_iter;
	}

	PointCloudIter(NearestPointIter&& near) {
		nearests = std::move(near);
		type     = nearest;
	}

	bool next(int64_t& x, int64_t& y, int64_t& z);
};


#endif // SRC_POINT_ITERS_HPP
