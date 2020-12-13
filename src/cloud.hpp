/*
See end of file for license
*/
#ifndef RFLANN_SRC_CLOUD_HPP_INCLUDED
#define RFLANN_SRC_CLOUD_HPP_INCLUDED

#include "link.h"
#include <stdint.h>
#include <vector>

struct Cloud {
	std::vector<PointIntern> points_;

	inline Cloud(std::vector<PointIntern>&& points) {
		points_ = std::move(points);
	}

	inline size_t kdtree_get_point_count() const { return points_.size(); }

	inline int64_t kdtree_get_pt(const size_t idx, const size_t dim) const {
		if (dim == 0) return points_[idx].x;
		if (dim == 1) return points_[idx].y;
		if (dim == 2) return points_[idx].z;
		return points_[idx].x; // This point should never be reached
	}

	// Don't actually know what this does
	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const { return false; }
};

#endif // RFLANN_SRC_CLOUD_HPP_INCLUDED
/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
