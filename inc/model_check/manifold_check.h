#ifndef MANIFOLD_CHECK_JJ_H
#define MANIFOLD_CHECK_JJ_H

#include <Eigen/Core>
#include <vector>
#include <array>


template<typename T>
struct Node
{
  Node()
    {
      node_left = nullptr;
      node_right = nullptr;
    }
  
  Eigen::Matrix<T, 3, 2> aabb;
  std::vector<size_t> table_tri;
  Node<T> *node_left;
  Node<T> *node_right;
};

template<typename T>
struct KdTree
{
  KdTree()
    {
      root = nullptr;
    }
  ~KdTree();
  
  int build_tree(const char* const path);
  Node<T>* setup_tree(const std::vector<size_t> &table_t, size_t axis);
  int get_tri_soup(const char *const path);
  int destory_tree(Node<T> *ptr);
  size_t get_tri_num() const;
  Eigen::Matrix<T, 3, 3> get_tri(size_t id_tri) const;
  std::vector<Eigen::Matrix<T, 3, 3>> get_neigh_tri(size_t id_tri) const;
  int get_neigh_tri(const Eigen::Matrix<T, 3, 2> &aabb, const Node<T> *const ptr, std::vector<size_t> &table_neigh_tri) const;
  Eigen::Matrix<T, 3, 2> get_aabb(
    const std::vector<size_t> &table_tri) const;

  std::vector<Eigen::Matrix<T, 3, 1>> get_tri_center(const std::vector<size_t> &table_t) const;

  Node<T> *root;
  std::vector<Eigen::Matrix<T, 3, 1>> table_vert;
  std::vector<Eigen::Matrix<size_t, 3, 1>> table_tri;
};

template<typename T>
bool is_mesh_self_intersection(const char *const path);


template<typename Derived>
bool is_triangle_triangle_self_intersect(const Eigen::MatrixBase<Derived> &tri_a, const Eigen::MatrixBase<Derived> &tri_b);

template<typename Derived>
bool is_triangle_degenerate(const Eigen::MatrixBase<Derived> &tri);

bool is_universal_connect(const std::array<int, 3> &position_a2b);

template<typename Derived>
int is_common_condition(const Eigen::MatrixBase<Derived> &tri_a, const Eigen::MatrixBase<Derived> &tri_b, const std::array<int, 3> &position_a2b, const std::array<int, 3> &position_b2a);

bool is_triangle_above_triangle(const std::array<int, 3> &position);

template<typename Derived>
bool is_triangle_to_triangle_intersect(const Eigen::MatrixBase<Derived> &tri_a, const Eigen::MatrixBase<Derived> &tri_b);

template<typename Derived>
bool is_triangle_triangle_self_intersect(const Eigen::MatrixBase<Derived> &tri_a, const Eigen::MatrixBase<Derived> &tri_b, const std::array<int, 3> &position_a2b, const std::array<int, 3> &position_b2a);

template<typename DerivedV, typename DerivedE>
bool is_vert_triangle_intersect(const Eigen::MatrixBase<DerivedV> &v, const Eigen::MatrixBase<DerivedV> &p, const Eigen::MatrixBase<DerivedE> &tri, bool coplanar_v_triangle = true);

template<typename Derived>
bool is_coplanar_triangle_triangle_intersect(const Eigen::MatrixBase<Derived> &tri_a, const Eigen::MatrixBase<Derived> &tri_b);

template<typename DerivedE, typename DerivedV, typename DerivedT>
bool is_coplanar_edge_triangle_intersect(const Eigen::MatrixBase<DerivedE> &e, const Eigen::MatrixBase<DerivedV> &p, const Eigen::MatrixBase<DerivedT> &tri);

template<typename DerivedE, typename DerivedT>
bool is_edge_triangle_intersect(const Eigen::MatrixBase<DerivedE> &e, const Eigen::MatrixBase<DerivedT> &tri);

template<typename DerivedE, typename DerivedV>
bool is_edge_edge_intersect(const Eigen::MatrixBase<DerivedE> &e, const Eigen::MatrixBase<DerivedE> &et, const Eigen::MatrixBase<DerivedV> &p);

#endif // MANIFOLD_CHECK_JJ_H
