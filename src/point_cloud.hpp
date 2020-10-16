#ifndef RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED
#define RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED

#include "link.h"
#include "nanoflann.hpp"
#include "cloud.hpp"

using namespace nanoflann;

using PointCloudKd = KDTreeSingleIndexDynamicAdaptor<
	L2_Adaptor<int64_t, Cloud>,
	Cloud,
	3>;
struct PointCloud: PointCloudKd {

	PointCloud(std::vector<PointIntern>&&);

	const std::vector<PointIntern>& get_underlying_buffer() const {
		return this->dataset.points_;
	}

};

#endif // RFLANN_SRC_POINT_CLOUD_HPP_INCLUDED
