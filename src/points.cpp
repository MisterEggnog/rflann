
#include <cstdint>
#include <vector>

#include "cloud.hpp"
#include "point_cloud.hpp"
#include "point_iters.hpp"
#include "link.h"


// Internal functions

PointCloud::PointCloud(std::vector<Point>&& cloud):
	PointCloudKd(3, Cloud(std::move(cloud)), KDTreeSingleIndexAdaptorParams(10)) {
}

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

// C wrapper functions

PointCloud*
new_cloud() {
	std::vector<Point> empty;
	return new PointCloud(std::move(empty));
}

PointCloud*
from_points(int64_t** array, size_t size) {
	std::vector<Point> points(size);
	for (size_t i = 0; i < size; i++) {
		points[i][0] = array[i][0];
		points[i][1] = array[i][1];
		points[i][2] = array[i][2];
	}
	return new PointCloud(std::move(points));
}

void
destroy_cloud(PointCloud* cloud) {
	delete cloud;
}

PointCloudIter*
get_points(const PointCloud* cloud) {
	auto& cloud_ = cloud->get_underlying_buffer();
	return new PointCloudIter(PointBufIter(cloud_.cbegin(), cloud_.cend()));
}

