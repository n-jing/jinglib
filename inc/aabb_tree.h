#ifndef AABB_TREE_JJ_H
#define AABB_TREE_JJ_H

#include <Eigen/Core>
#include <igl/AABB.h>
#include <string>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <igl/readSTL.h>
#include <igl/writeSTL.h>
#include <igl/readOFF.h>
#include <igl/writeOFF.h>
#include <memory>

//*****************************************************************************
//
//! \brief encapsulation of igl AABB, with template parameter dimension
//
//! Encapsulation of igl AABB, with geometry information(V, F) as member data.
//! \param DIM geometry dimension
//! \note igl AABB tree as member data, and Eigen::AlignedBox as member data of tree, IGL_INLINE bool intersect_ray funcion may be useful
//! \note AABBTree cannot use copy assignment and copy construction function
//
//*****************************************************************************

template <int DIM>
class AABBTree
{
  using IglAABB = igl::AABB<Eigen::MatrixXd, DIM>;
  using AABB = AABBTree<DIM>;
public:
  AABBTree(const AABBTree&) = delete;
  AABBTree &operator=(const AABBTree&) = delete;
  AABBTree() { left = nullptr; right = nullptr; } 

  AABBTree(const char *const path)
    {
      vert_ = std::make_shared<Eigen::MatrixXd>();
      face_ = std::make_shared<Eigen::MatrixXi>();
      normal_ = std::make_shared<Eigen::MatrixXd>();

      std::string ext(path);
      ext = ext.substr(ext.rfind(".") + 1);
      if (ext == "obj")
        igl::readOBJ(path, *vert_.get(), *face_.get());
      else if (ext == "stl")
        igl::readSTL(path, *vert_.get(), *face_.get(), *normal_.get());
      else if (ext == "off")
        igl::readOFF(path, *vert_.get(), *face_.get());
      else
        std::cout << "only obj, stl and off are supported" << std::endl;

      tree.init(*vert_.get(), *face_.get());
      init_aabb_tree(this);
    }
  AABBTree(const Eigen::MatrixXd &v,
           const Eigen::MatrixXi &f)
    {
      vert_ = std::make_shared<Eigen::MatrixXd>(v);
      face_ = std::make_shared<Eigen::MatrixXi>(f);
      tree.init(*vert_.get(), *face_.get());
      init_aabb_tree(this);
    }
  ~AABBTree() { destory_aabb_tree(); }

//! <get face geometry
//! \return face geometry  
  Eigen::MatrixXd get_face(size_t face_id) const
    {
      if (face_id >= face_->rows())
        return Eigen::MatrixXd();
      Eigen::MatrixXd face(DIM, face_->row(face_id).size());
      for (int i = 0; i < face_->row(face_id).size(); ++i)
        face.col(i) = vert_->row(face_->row(face_id)(i));
      return face;
    }
  void destory_aabb_tree()
    {
      delete left; left = nullptr;
      delete right; right = nullptr;
    }
//! encapsulation of igl AABB is_leaf
  bool is_leaf() const { return this->tree.is_leaf(); }
//! encapsulation of igl AABB m_primitive
  size_t get_face() const { return tree.m_primitive; }
//! get mesh element number
  size_t get_face_num() const { return face_->rows(); }
public:
  IglAABB tree;
  AABBTree<DIM> *left;
  AABBTree<DIM> *right;

private:
  void init_aabb_tree(AABB *const aabb_ptr)
    {
      if (aabb_ptr->tree.is_leaf())
      {
        aabb_ptr->left = nullptr; aabb_ptr->right = nullptr; return ;
      }
      aabb_ptr->left =
        new AABBTree(*aabb_ptr->tree.m_left, aabb_ptr->vert_, aabb_ptr->face_);
      aabb_ptr->right =
        new AABBTree(*aabb_ptr->tree.m_right, aabb_ptr->vert_, aabb_ptr->face_);
      init_aabb_tree(aabb_ptr->left);
      init_aabb_tree(aabb_ptr->right);
    }

  AABBTree(const IglAABB &t, const std::shared_ptr<Eigen::MatrixXd> &vert,
           const std::shared_ptr<Eigen::MatrixXi> &face) :
    tree(t), vert_(vert), face_(face) { }

  std::shared_ptr<Eigen::MatrixXd> vert_;
  std::shared_ptr<Eigen::MatrixXi> face_;
  std::shared_ptr<Eigen::MatrixXd> normal_;
};

#endif // AABB_TREE_JJ_H
