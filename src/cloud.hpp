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
