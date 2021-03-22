#ifndef REMVOE_DUPLICATE_VERTS_JJ_H
#define REMVOE_DUPLICATE_VERTS_JJ_H


#include <map>
#include <vector>
#include <unordered_map>
#include <Eigen/Core>
#include "key_comparison.h"


namespace Jing
{
  template<typename T=double, typename U=int>
  std::tuple<Eigen::Matrix<T, -1, -1>, Eigen::Matrix<U, -1, -1>> RemoveDuplicateVerts(const Eigen::Matrix<T, -1, -1> &verts, const Eigen::Matrix<U, -1, -1> &cells)
  {
    std::map<Eigen::Matrix<T, 3, 1>, int, KeyCompare<Eigen::Matrix<T, 3, 1>, 0>, 
             Eigen::aligned_allocator<std::pair<Eigen::Matrix<T, 3, 1>, int>>> verts_to_id;
    std::unordered_map<int, int> old_to_new_id;
    std::vector<Eigen::Matrix<T, 1, 3>,
                Eigen::aligned_allocator<Eigen::Matrix<T, 1, 3>>> unique_v;
    const int vert_num = verts.rows();
    for (int v = 0; v < vert_num; ++v)
    {
      if (!verts_to_id.count(verts.row(v)))
      {
        old_to_new_id.emplace(v, verts_to_id.size());
        verts_to_id.emplace(verts.row(v), verts_to_id.size());
        unique_v.push_back(verts.row(v));
      }
      else
        old_to_new_id.emplace(v, verts_to_id.at(verts.row(v)));
    }

    Eigen::Matrix<T, -1, -1> points(unique_v.size(), 3);
    for (int i = 0; i < unique_v.size(); ++i)
    {
      points.row(i) = unique_v[i];
    }
    const int CR = cells.rows();
    const int CC = cells.cols();
    Eigen::Matrix<U, -1, -1> grid = cells;
    for (int r = 0; r < CR; ++r)
    {
      for (int c = 0; c < CC; ++c)
      {
        grid(r, c) = old_to_new_id.at(grid(r, c));
      }
    }

    return {points, grid};
  }
}


#endif // REMVOE_DUPLICATE_VERTS_JJ_H
