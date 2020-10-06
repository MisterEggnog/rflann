
#include <cstdint>
#include <vector>
#include "nanoflann.hpp"

using Point = int64_t[3];

using namespace nanoflann;


// This should go in the include
struct PointCloudIter {
	virtual ~PointCloudIter() = 0;
	virtual bool next(int64_t& x, int64_t& y, int64_t& z) = 0;
};

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

struct Cloud {
	std::vector<Point> points_;

	inline size_t kdtree_get_point_count() const { return points_.size(); }

	inline int64_t kdtree_get_pt(const size_t idx, const size_t dim) const { return points_[idx][dim]; }

	// Don't actually know what this does
	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const { return false; }
};


using PointCloudKd = KDTreeSingleIndexDynamicAdaptor<
	L2_Adaptor<int64_t, Cloud>,
	Cloud,
	3>;

class PointCloud : PointCloudKd {
public:
	const std::vector<Point>& get_underlying_buffer() const {
		return this->dataset.points_;
	}

};

PointBufIter
get_points(const PointCloud& cloud) {
	auto& cloud_ = cloud.get_underlying_buffer();
	return PointBufIter{cloud_.cbegin(), cloud_.cend()};
}

// Iterator(s)

PointBufIter::PointBufIter(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end) {
	curr_ = begin;
	end_ = end;
}

bool
PointBufIter::next(int64_t& x, int64_t& y, int64_t& z) {
	if (curr_ >= end_)
		return false;
	auto& val_at = *curr_;
	x = val_at[0];
	y = val_at[1];
	z = val_at[2];
	curr_++;
	return true;
}
