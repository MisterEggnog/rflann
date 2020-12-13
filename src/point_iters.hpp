/*
See end of file for license
*/
#ifndef SRC_POINT_ITERS_HPP
#define SRC_POINT_ITERS_HPP

#include "point_cloud.hpp"

struct PointCloudIter {

	virtual ~PointCloudIter() = 0;

	virtual bool next(PointIntern& point) = 0;
};


class PointBufIter final: public PointCloudIter {
	std::vector<PointIntern>::const_iterator curr_, end_;
public:
	PointBufIter(std::vector<PointIntern>::const_iterator begin, std::vector<PointIntern>::const_iterator end);

	~PointBufIter() final;

	bool next(PointIntern& point) final;
};

class NearestPointIter final: public PointCloudIter {
	// TO DO
public:
	~NearestPointIter() final;

	bool next(PointIntern& point) final;
};


#endif // SRC_POINT_ITERS_HPP
/*
Copyright 2020 Baldwin, Josiah

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
