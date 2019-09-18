
#ifndef EIGEN_SPARSEVIEW_H
#define EIGEN_SPARSEVIEW_H

namespace internal {

template<typename MatrixType>
struct traits<SparseView<MatrixType> > : traits<MatrixType>
{
  typedef int Index;
  typedef Sparse StorageKind;
  enum {
    Flags = int(traits<MatrixType>::Flags) & (RowMajorBit)
  };
};

} // end namespace internal

template<typename MatrixType>
class SparseView : public SparseMatrixBase<SparseView<MatrixType> >
{
  typedef typename MatrixType::Nested MatrixTypeNested;
  typedef typename internal::remove_all<MatrixTypeNested>::type _MatrixTypeNested;
public:
  EIGEN_SPARSE_PUBLIC_INTERFACE(SparseView)

  SparseView(const MatrixType& mat, const Scalar& m_reference = Scalar(0),
             typename NumTraits<Scalar>::Real m_epsilon = NumTraits<Scalar>::dummy_precision()) : 
    m_matrix(mat), m_reference(m_reference), m_epsilon(m_epsilon) {}

  class InnerIterator;

  inline Index rows() const { return m_matrix.rows(); }
  inline Index cols() const { return m_matrix.cols(); }

  inline Index innerSize() const { return m_matrix.innerSize(); }
  inline Index outerSize() const { return m_matrix.outerSize(); }

protected:
  const MatrixTypeNested m_matrix;
  Scalar m_reference;
  typename NumTraits<Scalar>::Real m_epsilon;
};

template<typename MatrixType>
class SparseView<MatrixType>::InnerIterator : public _MatrixTypeNested::InnerIterator
{
public:
  typedef typename _MatrixTypeNested::InnerIterator IterBase;
  InnerIterator(const SparseView& view, Index outer) :
  IterBase(view.m_matrix, outer), m_view(view)
  {
    incrementToNonZero();
  }

  EIGEN_STRONG_INLINE InnerIterator& operator++()
  {
    IterBase::operator++();
    incrementToNonZero();
    return *this;
  }

  using IterBase::value;

protected:
  const SparseView& m_view;

private:
  void incrementToNonZero()
  {
    while(internal::isMuchSmallerThan(value(), m_view.m_reference, m_view.m_epsilon) && (bool(*this)))
      {
        IterBase::operator++();
      }
  }
};

template<typename Derived>
const SparseView<Derived> MatrixBase<Derived>::sparseView(const Scalar& m_reference,
                                                          typename NumTraits<Scalar>::Real m_epsilon) const
{
  return SparseView<Derived>(derived(), m_reference, m_epsilon);
}

#endif
