

#ifndef EIGEN_SPARSETRANSPOSE_H
#define EIGEN_SPARSETRANSPOSE_H

template<typename MatrixType> class TransposeImpl<MatrixType,Sparse>
  : public SparseMatrixBase<Transpose<MatrixType> >
{
    typedef typename internal::remove_all<typename MatrixType::Nested>::type _MatrixTypeNested;
  public:

    EIGEN_SPARSE_PUBLIC_INTERFACE(Transpose<MatrixType>)

    class InnerIterator;
    class ReverseInnerIterator;

    inline Index nonZeros() const { return derived().nestedExpression().nonZeros(); }
};

template<typename MatrixType> class TransposeImpl<MatrixType,Sparse>::InnerIterator
  : public _MatrixTypeNested::InnerIterator
{
    typedef typename _MatrixTypeNested::InnerIterator Base;
  public:

    EIGEN_STRONG_INLINE InnerIterator(const TransposeImpl& trans, Index outer)
      : Base(trans.derived().nestedExpression(), outer)
    {}
    inline Index row() const { return Base::col(); }
    inline Index col() const { return Base::row(); }
};

template<typename MatrixType> class TransposeImpl<MatrixType,Sparse>::ReverseInnerIterator
  : public _MatrixTypeNested::ReverseInnerIterator
{
    typedef typename _MatrixTypeNested::ReverseInnerIterator Base;
  public:

    EIGEN_STRONG_INLINE ReverseInnerIterator(const TransposeImpl& xpr, Index outer)
      : Base(xpr.derived().nestedExpression(), outer)
    {}
    inline Index row() const { return Base::col(); }
    inline Index col() const { return Base::row(); }
};

#endif // EIGEN_SPARSETRANSPOSE_H
