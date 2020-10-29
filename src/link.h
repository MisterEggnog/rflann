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

struct PointCloud* new_cloud();
struct PointCloud* from_points(struct PointIntern* array, size_t size);
void destroy_cloud(struct PointCloud* cloud);
void add_point(struct PointCloud* cloud, struct PointIntern* point);
struct PointCloudIter* get_points(const struct PointCloud* cloud);

void destroy_iter(struct PointCloudIter* iter);
int next(struct PointCloudIter* iter, struct PointIntern* point);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // RFLANN_SRC_LINK_H_INCLUDED
