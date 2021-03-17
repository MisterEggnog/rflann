/*
See end of file for license
*/
#ifndef RFLANN_SRC_LINK_HPP_INCLUDED
#define RFLANN_SRC_LINK_HPP_INCLUDED

#include <cstdint>
#include <cstddef>
#include <memory>
#include <rust/cxx.h>

struct PointIntern {
	int64_t x, y, z;
};

struct PointCloudIter {
	virtual ~PointCloudIter() = 0;
	virtual bool next(PointIntern& point) = 0;
};

struct PointCloud {
	PointCloud() noexcept;
	PointCloud(rust::Slice<const PointIntern> points) noexcept;
	PointCloud(PointCloud&&) noexcept = default;
	PointCloud(const PointCloud&) = delete;
	PointCloud& operator=(const PointCloud&) = delete;
	PointCloud& operator=(PointCloud&&) = default;

	void add_point(const PointIntern& point);

	std::unique_ptr<PointCloudIter> get_points() const;


private:
	struct Impl;
	std::unique_ptr<Impl> pimpl;
};


#if 0
struct PointCloud* new_cloud();
struct PointCloud* from_points(struct PointIntern* array, size_t size);
void destroy_cloud(struct PointCloud* cloud);
void add_point(struct PointCloud* cloud, struct PointIntern* point);
struct PointCloudIter* get_points(const struct PointCloud* cloud);

void destroy_iter(struct PointCloudIter* iter);
int next(struct PointCloudIter* iter, struct PointIntern* point);
#endif

#endif // RFLANN_SRC_LINK_HPP_INCLUDED
/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
