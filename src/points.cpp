/*
See end of file for license
*/
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
PointBufIter::next(PointIntern& point) {
	if (curr_ >= end_)
		return false;
	point = *curr_;
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

void
destroy_iter(PointCloudIter* iter) {
	delete iter;
}

int
next(PointCloudIter* iter, PointIntern* point) {
	return iter->next(*point);
}

/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
