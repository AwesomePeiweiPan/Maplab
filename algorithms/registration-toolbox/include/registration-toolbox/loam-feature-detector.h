#ifndef REGISTRATION_TOOLBOX_LOAM_FEATURE_DETECTOR_H_
#define REGISTRATION_TOOLBOX_LOAM_FEATURE_DETECTOR_H_

#include <utility>
#include <vector>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

template <typename T>
using PclPointCloudPtr = typename boost::shared_ptr<pcl::PointCloud<T>>;
using CurvaturePair = typename std::pair<size_t, double>;
using CurvaturePairs = typename std::vector<std::pair<size_t, double>>;

namespace regbox {

class LoamFeatureDetector {
 public:
  ~LoamFeatureDetector() = default;

  void extractLoamFeaturesFromPointCloud(
      const PclPointCloudPtr<pcl::PointXYZI>& point_cloud,
      PclPointCloudPtr<pcl::PointXYZI> feature_cloud);

 private:
  void extractFeaturesFromScanLine(
      const pcl::PointCloud<pcl::PointXYZI>::Ptr& scan_line,
      pcl::PointCloud<pcl::PointXYZI>::Ptr edges,
      pcl::PointCloud<pcl::PointXYZI>::Ptr surfaces);

  void extractFeaturesFromFeatureRegion(
      const pcl::PointCloud<pcl::PointXYZI>::Ptr& region_points,
      const CurvaturePairs& cloud_curvatures,
      pcl::PointCloud<pcl::PointXYZI>::Ptr edges,
      pcl::PointCloud<pcl::PointXYZI>::Ptr surfaces,
      std::vector<bool>* point_picked);

  void downSampleFeatures(
      pcl::PointCloud<pcl::PointXYZI>::Ptr edges,
      pcl::PointCloud<pcl::PointXYZI>::Ptr surfaces);

  void markUnstablePointsAsPicked(
      const pcl::PointCloud<pcl::PointXYZI>::Ptr& scan_line,
      std::vector<bool>* point_picked);

  void markCurvatureRegionAsPicked(
      const int& point_idx, std::vector<bool>* point_picked);

  void markFirstHalfCurvatureRegionAsPicked(
      const int& point_idx, std::vector<bool>* point_picked);
  void markSecondHalfCurvatureRegionAsPicked(
      const int& point_idx, std::vector<bool>* point_picked);

  void markCurvatureRegionAsPicked(
      const int& point_idx, const double& distance_threshold_m,
      const pcl::PointCloud<pcl::PointXYZI>::Ptr& scan_line,
      std::vector<bool>* point_picked);

  void calculateCurvatures(
      const pcl::PointCloud<pcl::PointXYZI>::Ptr& scan_line,
      CurvaturePairs* curvatures);
};

}  // namespace regbox

#endif  // REGISTRATION_TOOLBOX_LOAM_FEATURE_DETECTOR_H_