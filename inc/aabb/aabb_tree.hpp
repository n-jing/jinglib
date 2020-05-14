#include "aabb_tree.h"
#include <Eigen/Geometry> 
#include <vector>
#include <iostream>

using namespace std;

//*****************************************************************************
//
//! \brief get faces who boxes intersect the box of assigned face
//!
//! \param aabb_tree AABBTree
//! \param face_id index of assigned face
//!
//! \return table of intersect face
//!
//! \note 
//
//*****************************************************************************

template<int DIM>
std::vector<Eigen::MatrixXd> get_intersect_face(
  const AABBTree<DIM> &aabb_tree, size_t face_id)
{
  using AABBPtr = const AABBTree<DIM>*;
  Eigen::MatrixXd face = aabb_tree.get_face(face_id);
  Eigen::MatrixXd::Index face_index[DIM];
  Eigen::VectorXd max_bound(DIM);
  Eigen::VectorXd min_bound(DIM);
  for(int i = 0; i < DIM; ++i)
  {
    max_bound(i) = face.row(i).maxCoeff(&face_index[i]);
    min_bound(i) = face.row(i).minCoeff(&face_index[i]);
  } 
  const Eigen::AlignedBox<double, 3> face_box(min_bound, max_bound);
  vector<size_t> neighbor_face_id;
  stack<AABBPtr> stack_aabb;
  stack_aabb.push(&aabb_tree);
  while (!stack_aabb.empty())
  {
    AABBPtr ptr = stack_aabb.top();
    stack_aabb.pop();
    if (ptr->is_leaf())
      continue;
    if (face_box.intersects(ptr->tree.m_box))
    {
      if (ptr->is_leaf() && ptr->get_face_id() != face_id)
      {
        neighbor_face_id.push_back(ptr->get_face_id());
        continue;
      }  
      stack_aabb.push(ptr->left);
      stack_aabb.push(ptr->right);
    }
  }

  vector<Eigen::MatrixXd> neighbor_face;
  transform(neighbor_face_id.begin(), neighbor_face_id.end(),
            back_inserter(neighbor_face),
            [&aabb_tree] (size_t idx) -> Eigen::MatrixXd
            {
              return aabb_tree.get_face(idx);
            });

  return neighbor_face;
}
