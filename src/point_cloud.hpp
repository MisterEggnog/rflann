/*
See end of file for license
*/
#ifndef RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED
#define RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED

#include "link.hpp"
#include "nanoflann.hpp"
#include "cloud.hpp"

using namespace nanoflann;

using PointCloudKd = KDTreeSingleIndexDynamicAdaptor<
	L2_Adaptor<float, Cloud>,
	Cloud,
	3>;
struct PointCloud: PointCloudKd {

	PointCloud(std::vector<PointIntern>&&);

	const std::vector<PointIntern>& get_underlying_buffer() const {
		return this->dataset.points_;
	}

};

#endif // RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED
/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
