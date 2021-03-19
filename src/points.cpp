/*
See end of file for license
*/
#include <cstdint>
#include <vector>
#include "nanoflann.hpp"

#include "cloud.hpp"
#include "link.hpp"

namespace nf = nanoflann;

using PointCloudKd = nf::KDTreeSingleIndexDynamicAdaptor<
	nf::L2_Adaptor<float, Cloud>,
	Cloud,
	3>;

struct PointCloud::Impl: public PointCloudKd {
	Impl(std::vector<Point>&& points)
	: PointCloudKd(3, Cloud(std::move(points)), nf::KDTreeSingleIndexAdaptorParams(10)) {
	}

	const std::vector<Point>&
	get_underlying_buffer() const {
		return this->dataset.points_;
	}
};

class PointBufIter final: public PointCloudIter {
	std::vector<Point>::const_iterator curr_, end_;
public:
	PointBufIter(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end);

	~PointBufIter() final;

	bool next(Point& point) final;
};




// Internal functions

PointCloud::PointCloud() noexcept {
	std::vector<Point> empty;
	pimpl = std::make_unique<Impl>(std::move(empty));
}

PointCloud::PointCloud(rust::Slice<const Point> points) noexcept {
	std::vector<Point> vcpoints;
	vcpoints.reserve(points.size());
	for (const auto& point: points) {
		vcpoints.push_back(point);
	}
	pimpl = std::make_unique<Impl>(std::move(vcpoints));
}

std::unique_ptr<PointCloudIter>
PointCloud::get_points() const {
	auto& cloud_ = pimpl->get_underlying_buffer();
	return std::make_unique<PointBufIter>(cloud_.cbegin(), cloud_.cend());
}

PointBufIter::PointBufIter(std::vector<Point>::const_iterator begin, std::vector<Point>::const_iterator end) {
	curr_ = begin;
	end_ = end;
}

bool
PointBufIter::next(Point& point) {
	if (curr_ >= end_)
		return false;
	point = *curr_;
	curr_++;
	return true;
}


/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
