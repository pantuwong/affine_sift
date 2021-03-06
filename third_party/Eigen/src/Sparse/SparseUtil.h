
#ifndef EIGEN_SPARSEUTIL_H
#define EIGEN_SPARSEUTIL_H

#ifdef NDEBUG
#define EIGEN_DBG_SPARSE(X)
#else
#define EIGEN_DBG_SPARSE(X) X
#endif

#define EIGEN_SPARSE_INHERIT_ASSIGNMENT_OPERATOR(Derived, Op) \
template<typename OtherDerived> \
EIGEN_STRONG_INLINE Derived& operator Op(const Eigen::SparseMatrixBase<OtherDerived>& other) \
{ \
  return Base::operator Op(other.derived()); \
} \
EIGEN_STRONG_INLINE Derived& operator Op(const Derived& other) \
{ \
  return Base::operator Op(other); \
}

#define EIGEN_SPARSE_INHERIT_SCALAR_ASSIGNMENT_OPERATOR(Derived, Op) \
template<typename Other> \
EIGEN_STRONG_INLINE Derived& operator Op(const Other& scalar) \
{ \
  return Base::operator Op(scalar); \
}

#define EIGEN_SPARSE_INHERIT_ASSIGNMENT_OPERATORS(Derived) \
EIGEN_SPARSE_INHERIT_ASSIGNMENT_OPERATOR(Derived, =) \
EIGEN_SPARSE_INHERIT_ASSIGNMENT_OPERATOR(Derived, +=) \
EIGEN_SPARSE_INHERIT_ASSIGNMENT_OPERATOR(Derived, -=) \
EIGEN_SPARSE_INHERIT_SCALAR_ASSIGNMENT_OPERATOR(Derived, *=) \
EIGEN_SPARSE_INHERIT_SCALAR_ASSIGNMENT_OPERATOR(Derived, /=)

#define _EIGEN_SPARSE_PUBLIC_INTERFACE(Derived, BaseClass) \
  typedef BaseClass Base; \
  typedef typename Eigen::internal::traits<Derived>::Scalar Scalar; \
  typedef typename Eigen::NumTraits<Scalar>::Real RealScalar; \
  typedef typename Eigen::internal::nested<Derived>::type Nested; \
  typedef typename Eigen::internal::traits<Derived>::StorageKind StorageKind; \
  typedef typename Eigen::internal::traits<Derived>::Index Index; \
  enum { RowsAtCompileTime = Eigen::internal::traits<Derived>::RowsAtCompileTime, \
        ColsAtCompileTime = Eigen::internal::traits<Derived>::ColsAtCompileTime, \
        Flags = Eigen::internal::traits<Derived>::Flags, \
        CoeffReadCost = Eigen::internal::traits<Derived>::CoeffReadCost, \
        SizeAtCompileTime = Base::SizeAtCompileTime, \
        IsVectorAtCompileTime = Base::IsVectorAtCompileTime }; \
  using Base::derived; \
  using Base::const_cast_derived;

#define EIGEN_SPARSE_PUBLIC_INTERFACE(Derived) \
  _EIGEN_SPARSE_PUBLIC_INTERFACE(Derived, Eigen::SparseMatrixBase<Derived>)

const int CoherentAccessPattern     = 0x1;
const int InnerRandomAccessPattern  = 0x2 | CoherentAccessPattern;
const int OuterRandomAccessPattern  = 0x4 | CoherentAccessPattern;
const int RandomAccessPattern       = 0x8 | OuterRandomAccessPattern | InnerRandomAccessPattern;

template<typename Derived> class SparseMatrixBase;
template<typename _Scalar, int _Flags = 0, typename _Index = int>  class SparseMatrix;
template<typename _Scalar, int _Flags = 0, typename _Index = int>  class DynamicSparseMatrix;
template<typename _Scalar, int _Flags = 0, typename _Index = int>  class SparseVector;
template<typename _Scalar, int _Flags = 0, typename _Index = int>  class MappedSparseMatrix;

template<typename MatrixType, int Size>           class SparseInnerVectorSet;
template<typename MatrixType, int Mode>           class SparseTriangularView;
template<typename MatrixType, unsigned int UpLo>  class SparseSelfAdjointView;
template<typename Lhs, typename Rhs>              class SparseDiagonalProduct;
template<typename MatrixType> class SparseView;

template<typename Lhs, typename Rhs>        class SparseSparseProduct;
template<typename Lhs, typename Rhs>        class SparseTimeDenseProduct;
template<typename Lhs, typename Rhs>        class DenseTimeSparseProduct;
template<typename Lhs, typename Rhs, bool Transpose> class SparseDenseOuterProduct;

template<typename Lhs, typename Rhs> struct SparseSparseProductReturnType;
template<typename Lhs, typename Rhs, int InnerSize = internal::traits<Lhs>::ColsAtCompileTime> struct DenseSparseProductReturnType;
template<typename Lhs, typename Rhs, int InnerSize = internal::traits<Lhs>::ColsAtCompileTime> struct SparseDenseProductReturnType;

namespace internal {

template<typename T> struct eval<T,Sparse>
{
    typedef typename traits<T>::Scalar _Scalar;
    enum {
          _Flags = traits<T>::Flags
    };

  public:
    typedef SparseMatrix<_Scalar, _Flags> type;
};

template<typename T> struct plain_matrix_type<T,Sparse>
{
  typedef typename traits<T>::Scalar _Scalar;
    enum {
          _Flags = traits<T>::Flags
    };

  public:
    typedef SparseMatrix<_Scalar, _Flags> type;
};

} // end namespace internal

#endif // EIGEN_SPARSEUTIL_H
