
#include <cstdint>
#include <vector>
#include "nanoflann.hpp"

using Point = int64_t[3];

using namespace nanoflann;

struct Cloud {
	std::vector<Point> points_;

	inline size_t kdtree_get_point_count() const { return points_.size(); }

	inline int64_t kdtree_get_pt(const size_t idx, const size_t dim) const { return points_[idx][dim]; }

	// Don't actually know what this does
	template <class BBOX>
	bool kdtree_get_bbox(BBOX&) const { return false; }
};


using PointCloudKd = KDTreeSingleIndexDynamicAdaptor<
	L2_Adaptor<int64_t, Cloud>,
	Cloud,
	3>;

class PointCloud : PointCloudKd {

	const std::vector<Point>& get_underlying_buffer() const;

};

const std::vector<Point>&
PointCloud::get_underlying_buffer() const {
	return this->dataset.points_;
}

// Iterator(s)

struct PointCloudIter {
	virtual ~PointCloudIter() = 0;
	virtual Point const* next() = 0;
};

class PointBufIter: public PointCloudIter {
	std::vector<Point>::const_iterator begin_, end_;
public:
	override ~PointBufIter() = default;

	override Point const* next() {
		if (begin >= end_)
			return nullptr;
		auto point = *begin_;
		begin_++;
		return point;
	}
};

