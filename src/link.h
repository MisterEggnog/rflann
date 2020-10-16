#ifndef RFLANN_SRC_LINK_H_INCLUDED
#define RFLANN_SRC_LINK_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct PointIntern {
	int64_t x, y, z;
};

struct PointCloud;
struct PointCloudIter;

// All pointers passed are considered not null

PointCloud* new_cloud();
// Array is two dimensional array with a dim[n][3]
PointCloud* from_points(PointIntern* array, size_t size);
void destroy_cloud(PointCloud* cloud);
void add_point(PointCloud* cloud, PointIntern* point);
PointCloudIter* get_points(const PointCloud* cloud);

void destroy_iter(PointCloudIter* iter);
bool next(PointCloudIter* iter, PointIntern point);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // RFLANN_SRC_LINK_H_INCLUDED
