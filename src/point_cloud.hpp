#ifndef RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED
#define RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED

#include "nanoflann.hpp"
#include "cloud.hpp"

using namespace nanoflann;

using PointCloudKd = KDTreeSingleIndexDynamicAdaptor<
	L2_Adaptor<int64_t, Cloud>,
	Cloud,
	3>;
struct PointCloud: PointCloudKd {

	PointCloud(std::vector<Point>&&);

	const std::vector<Point>& get_underlying_buffer() const {
		return this->dataset.points_;
	}

};

#endif // RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED
