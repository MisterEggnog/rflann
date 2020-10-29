#ifndef SRC_POINT_ITERS_HPP
#define SRC_POINT_ITERS_HPP

#include "point_cloud.hpp"

struct PointCloudIter {

	virtual ~PointCloudIter() = 0;

	virtual bool next(int64_t& x, int64_t& y, int64_t& z) = 0;
};


class PointBufIter final: public PointCloudIter {
	std::vector<PointIntern>::const_iterator curr_, end_;
public:
	PointBufIter(std::vector<PointIntern>::const_iterator begin, std::vector<PointIntern>::const_iterator end);

	~PointBufIter() final;

	bool next(int64_t& x, int64_t& y, int64_t& z) final;
};

class NearestPointIter final: public PointCloudIter {
	// TO DO
public:
	~NearestPointIter() final;

	bool next(int64_t& x, int64_t& y, int64_t& z) final;
};


#endif // SRC_POINT_ITERS_HPP
