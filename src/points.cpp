/*
 * This file is under the BSD license.
 * See the end of the file for the full license agreement.
 */
#include <cassert>
#include <cstdint>
#include "nanoflann.hpp"

using point = int64_t[3];
using namespace nanoflann;

void get_points(point* buffer, size_t length, point vec);

struct point_cloud {
	const point* buffer_;
	size_t length_;

	size_t kdtree_get_point_count() const { return length_; }

	int64_t kdtree_get_pt(const size_t id, int dim) const {
		assert(id < length_);
		assert(dim < 3);
		return buffer_[id][dim];
	}

	// Not certain what this does
	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const { return false; }

	point_cloud(const point* buffer, size_t length) {
		buffer_ = buffer;
		length_ = length;
	}
};

void
get_points_dynamc(const point* buffer, size_t length, point vec) {
	auto cloud = point_cloud(buffer, length);
	using KDTree = KDTreeSingleIndexDynamicAdaptor<
		L2_Simple_Adaptor<int64_t, point_cloud>,
		point_cloud,
		3>;
}

void
get_points_static(const point* buffer, size_t length, point vec) {
	auto cloud = point_cloud(buffer, length);
}

int
main() {
}

/*
 * Software License Agreement (BSD License)
 *
 * Copyright 2020  Baldwin, Josiah.
 *   All rights reserved.
 *
 * THE BSD LICENSE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
