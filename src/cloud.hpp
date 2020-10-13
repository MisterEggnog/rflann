#ifndef RFLANN_SRC_CLOUD_HPP_INCLUDED
#define RFLANN_SRC_CLOUD_HPP_INCLUDED

#include <vector>

using Point = int64_t[3];

struct Cloud {
	std::vector<Point> points_;

	inline Cloud(std::vector<Point>&& points) {
		points_ = std::move(points);
	}

	inline size_t kdtree_get_point_count() const { return points_.size(); }

	inline int64_t kdtree_get_pt(const size_t idx, const size_t dim) const { return points_[idx][dim]; }

	// Don't actually know what this does
	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const { return false; }
};

#endif // RFLANN_SRC_CLOUD_HPP_INCLUDED
