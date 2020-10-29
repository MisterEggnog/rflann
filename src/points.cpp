
#include <cstdint>
#include <vector>

#include "cloud.hpp"
#include "point_cloud.hpp"
#include "point_iters.hpp"
#include "link.h"


// Internal functions

PointCloud::PointCloud(std::vector<PointIntern>&& cloud):
	PointCloudKd(3, Cloud(std::move(cloud)), KDTreeSingleIndexAdaptorParams(10)) {
}

PointBufIter::PointBufIter(std::vector<PointIntern>::const_iterator begin, std::vector<PointIntern>::const_iterator end) {
	curr_ = begin;
	end_ = end;
}

PointBufIter::~PointBufIter() = default;

bool
PointBufIter::next(int64_t& x, int64_t& y, int64_t& z) {
	if (curr_ >= end_)
		return false;
	auto& val_at = *curr_;
	x = val_at.x;
	y = val_at.y;
	z = val_at.z;
	curr_++;
	return true;
}

// C wrapper functions

PointCloud*
new_cloud() {
	std::vector<PointIntern> empty;
	return new PointCloud(std::move(empty));
}

PointCloud*
from_points(PointIntern* array, size_t size) {
	std::vector<PointIntern> points(size);
	points.reserve(size);
	for (size_t i = 0; i < size; i++)
		points.push_back(array[i]);
	return new PointCloud(std::move(points));
}

void
destroy_cloud(PointCloud* cloud) {
	delete cloud;
}

PointCloudIter*
get_points(const PointCloud* cloud) {
	auto& cloud_ = cloud->get_underlying_buffer();
	return new PointBufIter(cloud_.cbegin(), cloud_.cend());
}

