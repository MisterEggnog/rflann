
#include <cstdint>
#include <vector>

// This should go in the include
#include <stdint.h>
#include <stddef.h>

extern "C" {

struct PointCloud;
struct PointCloudIter;

// All pointers passed are considered not null

PointCloud* new_cloud();
PointCloud* from_points(int64_t** array, size_t size);
void destroy_cloud(PointCloud* cloud);
void add_point(PointCloud* cloud, int64_t* x, int64_t* y, int64_t* z);
PointCloudIter* get_points(const PointCloud* cloud);

void destroy_iter(PointCloudIter* iter);
bool next(PointCloudIter* iter, int64_t* x, int64_t* y, int64_t* z);

}

// End of fake include

#include "cloud.hpp"
#include "point_cloud.hpp"
#include "point_iters.hpp"


// Internal functions

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

PointCloudIter*
get_points(const PointCloud* cloud) {
	auto& cloud_ = cloud->get_underlying_buffer();
	return new PointCloudIter(PointBufIter(cloud_.cbegin(), cloud_.cend()));
}

