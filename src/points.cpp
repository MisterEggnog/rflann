
#include <cstdint>
#include <variant>
#include <vector>
#include "nanoflann.hpp"

using Point = int64_t[3];

using namespace nanoflann;


// This should go in the include
#include <stdint.h>

extern "C" {

struct PointCloud;
struct PointCloudIter;

PointCloud* new_cloud();
void destroy_cloud(PointCloud* cloud);
void add_point(PointCloud& cloud, int64_t& x, int64_t& y, int64_t& z);
PointCloudIter* get_points(const PointCloud& cloud);

void destroy_iter(PointCloudIter* iter);
bool next(PointCloudIter& iter, int64_t& x, int64_t& y, int64_t& z);

}

// End of fake include

struct PointCloudIter {
	std::variant<PointBufIter, NearestPointIter> tagged_union_;
};

class PointBufIter final {
	std::vector<Point>::const_iterator curr_, end_;
public:
	~PointBufIter() = default;

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
extern "C" {
struct PointCloud: PointCloudKd {
	const std::vector<Point>& get_underlying_buffer() const {
		return this->dataset.points_;
	}

};
}

PointCloudIter*
get_points(const PointCloud& cloud) {
	auto& cloud_ = cloud.get_underlying_buffer();
	return new PointBufIter(cloud_.cbegin(), cloud_.cend());
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
